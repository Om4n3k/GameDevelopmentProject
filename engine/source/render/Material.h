//
// Created by omank on 2.12.2025.
//

#pragma once
#include <memory>
#include <unordered_map>
#include <string>

namespace eng {
    class ShaderProgram;
    class Material {
    public:
        void SetShaderProgram(const std::shared_ptr<ShaderProgram>& shaderProgram);
        void SetParam(const std::string& name, float value);
        void Bind();
    private:
        std::shared_ptr<ShaderProgram> m_ShaderProgram;
        std::unordered_map<std::string, float> m_FloatProperties;
    };
}