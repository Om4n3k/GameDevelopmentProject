//
// Created by omank on 2.12.2025.
//

#pragma once
#include <memory>
#include <unordered_map>
#include <string>

namespace eng {
    class ShaderProgram;
    class Texture;
    class Material {
    public:
        ShaderProgram *GetShaderProgram() const;
        void SetShaderProgram(const std::shared_ptr<ShaderProgram>& shaderProgram);
        void SetParam(const std::string& name, float value);
        void SetParam(const std::string& name, float v0, float v1);
        void SetParam(const std::string& name, const std::shared_ptr<Texture>& texture);
        void Bind();
    private:
        std::shared_ptr<ShaderProgram> m_ShaderProgram;
        std::unordered_map<std::string, float> m_FloatProperties;
        std::unordered_map<std::string, std::pair<float,float>> m_FloatTupleProperties;
        std::unordered_map<std::string, std::shared_ptr<Texture>> m_Textures;
    };
}