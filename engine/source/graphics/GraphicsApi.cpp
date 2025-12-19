//
// Created by omank on 2.12.2025.
//

#include "GraphicsApi.h"
#include <iostream>

#include "ShaderProgram.h"
#include "render/Material.h"
#include "render/Mesh.h"

namespace eng {
    bool GraphicsApi::Init() {
        glEnable(GL_DEPTH_TEST);
        return true;
    }

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

    std::shared_ptr<ShaderProgram> & GraphicsApi::GetDefaultShaderProgram() {
        if (!m_DefaultShaderProgram) {
            std::string fragmentShaderSource = R"(
                #version 330 core

                struct Light {
                    vec3 color;
                    vec3 position;
                };
                uniform Light uLight;
                out vec4 FragColor;

                in vec2 vUV;
                in vec3 vNormal;
                in vec3 vFragPos;

                uniform sampler2D baseColorTxt;

                void main() {
                    vec3 norm = normalize(vNormal);
                    vec3 lightDir = normalize(uLight.position - vFragPos);
                    float diff = max(dot(norm, lightDir), 0.0);

                    vec3 diffuse = diff * uLight.color;

                    vec4 texColor = texture(baseColorTxt, vUV);
                    FragColor = texColor * vec4(diffuse, 1.0);
                }
            )";

            std::string vertexShaderSource = R"(
                #version 330 core
                layout (location = 0) in vec3 aPos;
                layout (location = 1) in vec3 aColor;
                layout (location = 2) in vec2 uV;
                layout (location = 3) in vec3 aNormal;

                out vec2 vUV;
                out vec3 vNormal;
                out vec3 vFragPos;

                uniform mat4 uModel;
                uniform mat4 uView;
                uniform mat4 uProjection;

                void main() {
                    vUV = uV;

                    vFragPos = vec3(uModel * vec4(aPos, 1.0));
                    vNormal = mat3(transpose(inverse(uModel))) * aNormal;

                    gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);
                }
            )";

            m_DefaultShaderProgram = CreateShaderProgram(vertexShaderSource, fragmentShaderSource);
        }
        return m_DefaultShaderProgram;
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
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
