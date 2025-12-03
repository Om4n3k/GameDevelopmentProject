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

    void RenderQueue::Draw(GraphicsApi &graphicsApi) {
        for (auto& command : m_Commands) {
            graphicsApi.BindMaterial(command.material);
            command.material->GetShaderProgram()->SetUniform("uModel", command.modelMatrix);
            graphicsApi.BindMesh(command.mesh);
            graphicsApi.DrawMesh(command.mesh);
        }

        m_Commands.clear();
    }
}
