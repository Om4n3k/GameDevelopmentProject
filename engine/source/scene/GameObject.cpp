//
// Created by omank on 2.12.2025.
//

#include "GameObject.h"
#include <glm/gtc/matrix_transform.hpp>

#include "Component.h"
#include <glm/gtc/quaternion.hpp>
#define CGLTF_IMPLEMENTATION
#include <cgltf.h>

#include "Engine.h"
#include "Scene.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "components/MeshComponent.h"
#include "graphics/Texture.h"
#include "graphics/VertexLayout.h"
#include "render/Material.h"
#include "render/Mesh.h"

namespace eng {
    size_t Component::nextId = 1;

    void ParseGLTFNode(cgltf_node* node, GameObject* parent, const std::filesystem::path& folder) {
        auto obj = parent->GetScene()->CreateObject(node->name, parent);

        auto readFloats = [](const cgltf_accessor *acc, cgltf_size i, float *out, int n) {
            std::fill(out, out + n, 0.0f);
            cgltf_accessor_read_float(acc, i, out, n) == 1;
        };

        auto readIndex = [](const cgltf_accessor *acc, cgltf_size i) {
            cgltf_uint out = 0;
            cgltf_bool ok = cgltf_accessor_read_uint(acc, i, &out, 1);
            return ok ? static_cast<uint32_t>(out) : 0;
        };

        if (node->has_matrix) {
            auto mat = glm::make_mat4(node->matrix);
            glm::vec3 translation, scale, skew;
            glm::vec4 perspective;
            glm::quat orientation;
            glm::decompose(mat, scale, orientation, translation, skew, perspective);

            obj->SetPosition(translation);
            obj->SetRotation(orientation);
            obj->SetScale(scale);
        } else {
            if (node->has_translation) {
                obj->SetPosition(glm::vec3(node->translation[0], node->translation[1], node->translation[2]));
            }
            if (node->has_rotation) {
                obj->SetRotation(glm::quat(node->rotation[3], node->rotation[0], node->rotation[1], node->rotation[2]));
            }
            if (node->has_scale) {
                obj->SetScale(glm::vec3(node->scale[0], node->scale[1], node->scale[2]));
            }
        }

        if (node->mesh) {
            for (cgltf_size pi = 0; pi < node->mesh->primitives_count; ++pi) {
                auto& primitive = node->mesh->primitives[pi];
                if (primitive.type != cgltf_primitive_type_triangles) continue;

                VertexLayout vertexLayout;
                cgltf_accessor *accessors[4] = {nullptr, nullptr, nullptr, nullptr};

                for (cgltf_size ai = 0; ai < primitive.attributes_count; ++ai) {
                    auto &attr = primitive.attributes[ai];
                    auto acc = attr.data;
                    if (!acc) continue;

                    VertexElement element;
                    element.type = GL_FLOAT;
                    switch (attr.type) {
                        case cgltf_attribute_type_position: {
                            accessors[VertexElement::PositionIndex] = acc;
                            element.index = VertexElement::PositionIndex;
                            element.size = 3;
                        }
                            break;
                        case cgltf_attribute_type_color: {
                            if (attr.index != 0) continue;
                            accessors[VertexElement::ColorIndex] = acc;
                            element.index = VertexElement::PositionIndex;
                            element.size = 3;
                        }
                            break;
                        case cgltf_attribute_type_texcoord: {
                            if (attr.index != 0) continue;
                            accessors[VertexElement::UVIndex] = acc;
                            element.index = VertexElement::UVIndex;
                            element.size = 2;
                        }
                            break;
                        case cgltf_attribute_type_normal: {
                            accessors[VertexElement::NormalIndex] = acc;
                            element.index = VertexElement::NormalIndex;
                            element.size = 3;
                        }
                            break;
                        default: continue;
                    }

                    element.offset = vertexLayout.stride;
                    vertexLayout.stride += element.size * sizeof(float);
                    vertexLayout.elements.push_back(element);
                }

                if (!accessors[VertexElement::PositionIndex]) continue;
                auto vertexCount = accessors[VertexElement::PositionIndex]->count;

                std::vector<float> vertices;
                vertices.resize(vertexLayout.stride / sizeof(float) * vertexCount);

                for (cgltf_size vi = 0; vi < vertexCount; ++vi) {
                    for (auto &el: vertexLayout.elements) {
                        if (!accessors[el.index]) continue;
                        auto index = (vi * vertexLayout.stride + el.offset) / sizeof(float);
                        float *outData = &vertices[index];
                        readFloats(accessors[el.index], vi, outData, el.size);
                    }
                }

                std::shared_ptr<Mesh> mesh;
                if (primitive.indices) {
                    auto indexCount = primitive.indices->count;
                    std::vector<uint32_t> indices(indexCount);
                    for (cgltf_size i = 0; i < indexCount; ++i) {
                        indices[i] = readIndex(primitive.indices, i);
                    }
                    mesh = std::make_shared<Mesh>(vertexLayout, vertices, indices);
                } else {
                    mesh = std::make_shared<Mesh>(vertexLayout, vertices);
                }

                auto mat = std::make_shared<Material>();
                mat->SetShaderProgram(Engine::GetInstance().GetGraphicsApi().GetDefaultShaderProgram());

                if (primitive.material) {
                    auto gltfMat = primitive.material;
                    if (gltfMat->has_pbr_metallic_roughness) {
                        auto pbr = gltfMat->pbr_metallic_roughness;
                        auto texture = pbr.base_color_texture.texture;
                        if (texture && texture->image) {
                            if (texture->image->uri) {
                                auto path = folder / std::string(texture->image->uri);
                                auto tex = Texture::Load(path.string());
                                mat->SetParam("baseColorTxt", tex);
                            }
                        }
                    }
                    else if (gltfMat->has_pbr_specular_glossiness) {
                        auto pbr = gltfMat->pbr_specular_glossiness;
                        auto texture = pbr.diffuse_texture.texture;
                        if (texture && texture->image) {
                            if (texture->image->uri) {
                                auto path = folder / std::string(texture->image->uri);
                                auto tex = Texture::Load(path.string());
                                mat->SetParam("baseColorTxt", tex);
                            }
                        }
                    }

                    obj->AddComponent(new MeshComponent(mat, mesh));
                }
            }
        }

        for (cgltf_size ci = 0; ci < node->children_count; ++ci) {
            ParseGLTFNode(node->children[ci], obj, folder);
        }
    }

    GameObject * GameObject::LoadGLTF(const std::string &path, const std::string &name) {
        auto& fs = Engine::GetInstance().GetFileSystem();
        const auto contents = fs.LoadAssetFileText(path);
        if (contents.empty()) {return nullptr;}

        constexpr cgltf_options options{};
        cgltf_data* data = nullptr;
        cgltf_result res = cgltf_parse(&options, contents.data(), contents.size(), &data);
        if (res != cgltf_result_success) {
            return nullptr;
        }

        auto fullPath = fs.GetAssetsFolder() / path;
        auto fullFolderPath = fullPath.remove_filename();
        auto relativeFolderPath = std::filesystem::path(path).remove_filename();

        res = cgltf_load_buffers(&options, data, fullFolderPath.string().c_str());
        if (res != cgltf_result_success) {
            cgltf_free(data);
            return nullptr;
        }

        auto resultObj = Engine::GetInstance().GetCurrentScene()->CreateObject(name);
        auto scene = &data->scenes[0];

        for (cgltf_size i = 0; i < scene->nodes_count; ++i) {
            auto node = scene->nodes[i];
            ParseGLTFNode(node, resultObj, relativeFolderPath);
        }

        cgltf_free(data);
        return resultObj;
    }

    void GameObject::Update(float deltaTime) {
        for (auto & component : m_Components) {
            component->Update(deltaTime);
        }
        for (auto it = m_Children.begin(); it != m_Children.end(); ) {
            if ((*it)->IsAlive()) {
                (*it)->Update(deltaTime);
                ++it;
            }
            else {
                it = m_Children.erase(it);
            }
        }
    }

    const std::string &GameObject::GetName() {
        return m_Name;
    }

    void GameObject::SetName(const std::string &name) {
        m_Name = name;
    }

    GameObject* GameObject::GetParent() const {
        return m_Parent;
    }

    Scene * GameObject::GetScene() const {
        return m_Scene;
    }

    bool GameObject::SetParent(GameObject *parent) {
        if (!m_Scene) return false;
        return m_Scene->SetParent(this, parent);
    }

    bool GameObject::IsAlive() const {
        return m_IsAlive;
    }

    void GameObject::MarkForDestroy() {
        m_IsAlive = false;
    }

    void GameObject::AddComponent(Component *component) {
        m_Components.emplace_back(component);
        component->m_Owner = this;
    }

    glm::vec3 GameObject::GetPosition() const {
        return m_Position;
    }

    glm::vec3 GameObject::GetWorldPosition() const {
        glm::vec4 hom = GetWorldTransform() * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        return glm::vec3(hom) / hom.w; //TODO: Or /divide by w?
    }

    void GameObject::SetPosition(const glm::vec3 &position) {
        m_Position = position;
    }

    glm::quat GameObject::GetRotation() const {
        return m_Rotation;
    }

    void GameObject::SetRotation(const glm::quat &rotation) {
        m_Rotation = rotation;
    }

    glm::vec3 GameObject::GetScale() const {
        return m_Scale;
    }

    void GameObject::SetScale(const glm::vec3 &scale) {
        m_Scale = scale;
    }

    glm::mat4 GameObject::GetLocalTransform() const {
        auto mat = glm::mat4(1.0f);

        // Translation
        mat = glm::translate(mat, m_Position);

        // Rotation
        mat = mat * glm::mat4_cast(m_Rotation);

        // Scale
        mat = glm::scale(mat, m_Scale);

        return mat;
    }

    glm::mat4 GameObject::GetWorldTransform() const {
        if (m_Parent) {
            return m_Parent->GetWorldTransform() * GetLocalTransform();
        }
        return GetLocalTransform();
    }
}
