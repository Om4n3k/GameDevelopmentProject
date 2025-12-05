//
// Created by omank on 2.12.2025.
//

#include "RenderQueue.h"
#include "graphics/GraphicsApi.h"
#include "graphics/ShaderProgram.h"
#include "render/Material.h"

namespace eng {
    void RenderQueue::Submit(const RenderCommand &command) {
        m_Commands.push_back(command);
    }

    void RenderQueue::Draw(GraphicsApi &graphicsApi, const CameraData &cameraData) {
        for (auto& command : m_Commands) {
            graphicsApi.BindMaterial(command.material);
            auto shaderProgram = command.material->GetShaderProgram();
            shaderProgram->SetUniform("uModel", command.modelMatrix);
            shaderProgram->SetUniform("uView", cameraData.viewMatrix);
            shaderProgram->SetUniform("uProjection", cameraData.projectionMatrix);
            graphicsApi.BindMesh(command.mesh);
            graphicsApi.DrawMesh(command.mesh);
        }

        m_Commands.clear();
    }
}
