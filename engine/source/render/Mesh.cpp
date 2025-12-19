//
// Created by omank on 2.12.2025.
//

#include "Mesh.h"
#include "graphics/GraphicsApi.h"
#include "Engine.h"

namespace eng {
    Mesh::Mesh(const VertexLayout &layout, const std::vector<float> &vertices, const std::vector<uint32_t> &indices) {
        m_VertexLayout = layout;

        auto &graphicsApi = Engine::GetInstance().GetGraphicsApi();

        m_VBO = graphicsApi.CreateVertexBuffer(vertices);
        m_EBO = graphicsApi.CreateIndexBuffer(indices);

        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);

        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        for (auto &element: m_VertexLayout.elements) {
            glVertexAttribPointer(element.index, element.size, element.type, GL_FALSE, m_VertexLayout.stride,
                                  (void *) (uintptr_t) (element.offset));
            glEnableVertexAttribArray(element.index);
        }

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        m_VertexCount = vertices.size() * sizeof(float) / m_VertexLayout.stride;
        m_IndexCount = indices.size();
    }

    Mesh::Mesh(const VertexLayout &layout, const std::vector<float> &vertices) {
        m_VertexLayout = layout;

        auto &graphicsApi = Engine::GetInstance().GetGraphicsApi();

        m_VBO = graphicsApi.CreateVertexBuffer(vertices);

        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);

        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        for (auto &element: m_VertexLayout.elements) {
            glVertexAttribPointer(element.index, element.size, element.type, GL_FALSE, m_VertexLayout.stride,
                                  (void *) (uintptr_t) (element.offset));
            glEnableVertexAttribArray(element.index);
        }

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        m_VertexCount = vertices.size() * sizeof(float) / m_VertexLayout.stride;
    }

    void Mesh::Bind() {
        glBindVertexArray(m_VAO);
    }

    void Mesh::Draw() {
        if (m_IndexCount > 0) {
            glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, 0);
        } else {
            glDrawArrays(GL_TRIANGLES, 0, m_VertexCount);
        }
    }

    std::shared_ptr<Mesh> Mesh::CreateCube() {
        std::vector<float> cubeVertices = {
            // Front face
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,

            // Top face
            0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

            // Right face
            0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,

            // Left face
            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,

            // Bottom face
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,

            // Back face
            -0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        };

        std::vector<unsigned int> indicies = {
            // front face
            0, 1, 2,
            0, 2, 3,

            // top face
            4, 5, 6,
            4, 6, 7,

            // right face
            8, 9, 10,
            8, 10, 11,

            // left face
            12, 13, 14,
            12, 14, 15,

            // bottom face
            16, 17, 18,
            16, 18, 19,

            // back face
            20, 21, 22,
            20, 22, 23
        };

        eng::VertexLayout vertexLayout;
        vertexLayout.elements.push_back({
            VertexElement::PositionIndex,
            3,
            GL_FLOAT,
            0
        });
        vertexLayout.elements.push_back({
            VertexElement::ColorIndex,
            3,
            GL_FLOAT,
            sizeof(float) * 3,
        });
        vertexLayout.elements.push_back({
            VertexElement::UVIndex,
            2,
            GL_FLOAT,
            sizeof(float) * 6,
        });
        vertexLayout.elements.push_back({
            VertexElement::NormalIndex,
            3,
            GL_FLOAT,
            sizeof(float) * 8
        });
        vertexLayout.stride = sizeof(float) * 11;

        auto mesh = std::make_shared<Mesh>(vertexLayout, cubeVertices, indicies);
        return mesh;
    }
} // eng
