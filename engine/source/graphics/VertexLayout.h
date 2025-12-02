//
// Created by omank on 2.12.2025.
//
#pragma once
#include <vector>

namespace eng {
    struct VertexElement {
        GLuint index; // Attribute index (location) in the shader
        GLuint size; // Number of components (e.g., 3 for vec3)
        GLuint type; // Data type (e.g., GL_FLOAT)
        uint32_t offset; // Offset in bytes from the start of the vertex (e.g 0 for position)
    };

    struct VertexLayout {
        std::vector<VertexElement> elements;
        uint32_t stride = 0; // Total size of a single vertex in bytes
    };
}