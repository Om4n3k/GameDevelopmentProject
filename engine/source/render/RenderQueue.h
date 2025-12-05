//
// Created by omank on 2.12.2025.
//
#pragma once
#include <vector>
#include <glm/mat4x4.hpp>

namespace eng {
    class Mesh;
    class Material;
    class GraphicsApi;

    struct RenderCommand {
        Mesh *mesh = nullptr;
        Material *material = nullptr;
        glm::mat4 modelMatrix = glm::mat4(1.0f);
    };

    struct CameraData {
        glm::mat4 viewMatrix;
        glm::mat4 projectionMatrix;
    };

    class RenderQueue {
    public:
        void Submit(const RenderCommand &command);
        void Draw(GraphicsApi& graphicsApi, const CameraData& cameraData);

    private:
        std::vector<RenderCommand> m_Commands;
    };
}
