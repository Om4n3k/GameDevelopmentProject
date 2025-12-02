//
// Created by omank on 2.12.2025.
//

#include "GraphicsApi.h"
#include <iostream>

#include "ShaderProgram.h"
#include "render/Material.h"
#include "render/Mesh.h"

namespace eng {
    std::shared_ptr<ShaderProgram> GraphicsApi::CreateShaderProgram(const std::string &vertexSource, const std::string &fragmentSource) {
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        const char* vertexShaderCStr = vertexSource.c_str();
        glShaderSource(vertexShader, 1, &vertexShaderCStr, nullptr);
        glCompileShader(vertexShader);

        GLint success;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
            std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
            return nullptr;
        }

        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        const char* fragmentShaderCStr = fragmentSource.c_str();
        glShaderSource(fragmentShader, 1, &fragmentShaderCStr, nullptr);
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
            std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
            return nullptr;
        }

        GLuint shaderProgramId = glCreateProgram();
        glAttachShader(shaderProgramId, vertexShader);
        glAttachShader(shaderProgramId, fragmentShader);
        glLinkProgram(shaderProgramId);

        glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetProgramInfoLog(shaderProgramId, 512, nullptr, infoLog);
            std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
            return nullptr;
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return std::make_shared<ShaderProgram>(shaderProgramId);
    }

    GLuint GraphicsApi::CreateVertexBuffer(const std::vector<float> &vertices) {
        GLuint VBO = 0;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        return VBO;
    }

    GLuint GraphicsApi::CreateIndexBuffer(const std::vector<uint32_t> &indices) {
        GLuint EBO = 0;
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        return EBO;
    }

    void GraphicsApi::SetClearColor(float r, float g, float b, float a) {
        glClearColor(r,g,b,a);
    }

    void GraphicsApi::ClearBuffers() {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void GraphicsApi::BindShaderProgram(ShaderProgram *shaderProgram) {
        if (shaderProgram) {
            shaderProgram->Bind();
        }
    }

    void GraphicsApi::BindMaterial(Material *material) {
        if (material) {
            material->Bind();
        }
    }

    void GraphicsApi::BindMesh(Mesh *mesh) {
        if (mesh) {
            mesh->Bind();
        }
    }

    void GraphicsApi::DrawMesh(Mesh *mesh) {
        if (mesh) {
            mesh->Draw();
        }
    }
}
