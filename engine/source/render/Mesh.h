//
// Created by omank on 2.12.2025.
//

#pragma once
#include <GL/glew.h>
#include "graphics/VertexLayout.h"

namespace eng {
    class Mesh {
    public:
        Mesh(const VertexLayout& layout, const std::vector<float>& vertices, const std::vector<uint32_t>& indices);
        Mesh(const VertexLayout& layout, const std::vector<float>& vertices);

        Mesh(const Mesh&) = delete;
        Mesh& operator=(const Mesh&) = delete;

        void Bind();
        void Draw();
    private:
        VertexLayout m_VertexLayout;
        size_t m_VertexCount = 0;
        size_t m_IndexCount = 0;
        GLuint m_VBO = 0; // Vertex buffer object
        GLuint m_EBO = 0; // Element buffer object
        GLuint m_VAO = 0; // Vertex array object
    };
}