//
// Created by omank on 2.12.2025.
//
#pragma once
#include <string>
#include <unordered_map>
#include <GL/glew.h>

#include "glm/ext/matrix_float4x4.hpp"

namespace eng {
    class ShaderProgram {
    public:
        ShaderProgram() = delete;
        ShaderProgram(const ShaderProgram&) = delete;
        ShaderProgram& operator=(const ShaderProgram&) = delete;
        explicit ShaderProgram(GLuint shaderProgramId);
        ~ShaderProgram();

        void Bind() const;
        GLint GetUniformLocation(const std::string& name);
        void SetUniform(const std::string& name, float value);
        void SetUniform(const std::string& name, float v0, float v1);
        void SetUniform(const std::string& name, const glm::mat4& mat);
    private:
        std::unordered_map<std::string, GLint> m_UniformLocationCache;
        GLuint m_ShaderProgramID = 0;
    };
}
