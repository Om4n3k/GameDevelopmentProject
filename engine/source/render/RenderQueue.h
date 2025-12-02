//
// Created by omank on 2.12.2025.
//
#pragma once
#include <vector>

namespace eng {
    class Mesh;
    class Material;
    class GraphicsApi;

    struct RenderCommand {
        Mesh *mesh = nullptr;
        Material *material = nullptr;
    };

    class RenderQueue {
    public:
        void Submit(const RenderCommand &command);
        void Draw(GraphicsApi& graphicsApi);

    private:
        std::vector<RenderCommand> m_Commands;
    };
}
