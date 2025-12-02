//
// Created by omank on 2.12.2025.
//
#pragma once

#include <GL/glew.h>
#include <memory>
#include <string>
#include <vector>

namespace eng {
    class Material;
    class ShaderProgram;
    class GraphicsApi {
    public:
        std::shared_ptr<ShaderProgram> CreateShaderProgram(const std::string& vertexSource, const std::string& fragmentSource);

        GLuint CreateVertexBuffer(const std::vector<float>& vertices);
        GLuint CreateIndexBuffer(const std::vector<uint32_t>& indices);

        void BindShaderProgram(ShaderProgram* shaderProgram);
        void BindMaterial(Material* material);
    };
}
