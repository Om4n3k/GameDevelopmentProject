//
// Created by omank on 5.12.2025.
//

#include "MeshComponent.h"

#include "Engine.h"
#include "render/RenderQueue.h"
#include "scene/GameObject.h"

namespace eng {
    MeshComponent::MeshComponent(const std::shared_ptr<Material> &material, const std::shared_ptr<Mesh> &mesh)
        : m_Material(material), m_Mesh(mesh) {

    }

    void MeshComponent::Update(float deltaTime) {
        if (!m_Material || !m_Mesh) {
            return;
        }

        RenderCommand renderCommand;
        renderCommand.material = m_Material.get();
        renderCommand.mesh = m_Mesh.get();
        renderCommand.modelMatrix = GetOwner()->GetWorldTransform();

        auto& renderQueue = Engine::GetInstance().GetRenderQueue();
        renderQueue.Submit(renderCommand);
    }
} // eng