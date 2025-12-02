//
// Created by omank on 2.12.2025.
//

#include "Material.h"
#include "graphics/ShaderProgram.h"

namespace eng {
    void Material::SetShaderProgram(const std::shared_ptr<ShaderProgram>& shaderProgram) {
        m_ShaderProgram = shaderProgram;
    }

    void Material::SetParam(const std::string &name, float value) {
        m_FloatProperties[name] = value;
    }

    void Material::Bind() {
        if (!m_ShaderProgram) {
            return;
        }
        m_ShaderProgram->Bind();
        for (const auto& param : m_FloatProperties) {
            m_ShaderProgram->SetUniform(param.first, param.second);
        }
    }
}
