//
// Created by omank on 2.12.2025.
//

#include "Mesh.h"
#include "graphics/GraphicsApi.h"
#include "Engine.h"

namespace eng {
    Mesh::Mesh(const VertexLayout &layout, const std::vector<float> &vertices, const std::vector<uint32_t> &indices) {
        m_VertexLayout = layout;

        auto& graphicsApi = Engine::GetInstance().GetGraphicsApi();

        m_VBO = graphicsApi.CreateVertexBuffer(vertices);
        m_EBO = graphicsApi.CreateIndexBuffer(indices);

        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);

        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        for (auto& element : m_VertexLayout.elements) {
            glVertexAttribPointer(element.index, element.size, element.type, GL_FALSE, m_VertexLayout.stride, (void*)(uintptr_t)(element.offset));
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

        auto& graphicsApi = Engine::GetInstance().GetGraphicsApi();

        m_VBO = graphicsApi.CreateVertexBuffer(vertices);

        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);

        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        for (auto& element : m_VertexLayout.elements) {
            glVertexAttribPointer(element.index, element.size, element.type, GL_FALSE, m_VertexLayout.stride, (void*)(uintptr_t)(element.offset));
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
} // eng