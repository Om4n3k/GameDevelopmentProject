//
// Created by omank on 2.12.2025.
//

#include "Material.h"

#include "Engine.h"
#include "graphics/ShaderProgram.h"
#include "graphics/Texture.h"
#include "nlohmann/json.hpp"

namespace eng {
    ShaderProgram * Material::GetShaderProgram() const {
        return m_ShaderProgram.get();
    }

    void Material::SetShaderProgram(const std::shared_ptr<ShaderProgram>& shaderProgram) {
        m_ShaderProgram = shaderProgram;
    }

    void Material::SetParam(const std::string &name, float value) {
        m_FloatProperties[name] = value;
    }

    void Material::SetParam(const std::string &name, float v0, float v1) {
        m_FloatTupleProperties[name] = {v0, v1};
    }

    void Material::SetParam(const std::string &name, const std::shared_ptr<Texture> &texture) {
        m_Textures[name] = texture;
    }

    void Material::Bind() {
        if (!m_ShaderProgram) {
            return;
        }

        m_ShaderProgram->Bind();

        for (const auto& param : m_FloatProperties) {
            m_ShaderProgram->SetUniform(param.first, param.second);
        }

        for (const auto& param : m_FloatTupleProperties) {
            m_ShaderProgram->SetUniform(param.first, param.second.first, param.second.second);
        }

        for (const auto& texture : m_Textures) {
            m_ShaderProgram->SetTexture(texture.first, texture.second.get());
        }
    }

    std::shared_ptr<Material> Material::Load(const std::string &path) {
        auto& fs = Engine::GetInstance().GetFileSystem();
        auto contents = fs.LoadAssetFileText("materials/brick.json");
        if (contents.empty()) return nullptr;

        nlohmann::json json = nlohmann::json::parse(contents);
        std::shared_ptr<Material> result;

        if (json.contains("shader")) {
            auto shaderObj = json["shader"];
            std::string vertexPath = shaderObj.value("vertex", "");
            std::string fragmentPath = shaderObj.value("fragment", "");

            auto vertexSrc = fs.LoadAssetFileText(vertexPath);
            auto fragmentSrc = fs.LoadAssetFileText(fragmentPath);

            auto& graphicsApi = Engine::GetInstance().GetGraphicsApi();
            auto shaderProgram = graphicsApi.CreateShaderProgram(vertexSrc, fragmentSrc);
            if (!shaderProgram) {
                return nullptr;
            }

            result = std::make_shared<Material>();
            result->SetShaderProgram(shaderProgram);
        }

        if (json.contains("params")) {
            auto paramsObj = json["params"];
            // Floats
            if (paramsObj.contains("float")) {
                for (auto& p : paramsObj["float"]) {
                    std::string name = p.value("name", "");
                    float value = p.value("value", 0.0f);
                    result->SetParam(name, value);
                }
            }
            if (paramsObj.contains("float2")) {
                for (auto& p : paramsObj["float2"]) {
                    std::string name = p.value("name", "");
                    float v0 = p.value("value0", 0.0f);
                    float v1 = p.value("value1", 0.0f);
                    result->SetParam(name, v0, v1);
                }
            }
            if (paramsObj.contains("textures")) {
                for (auto& p : paramsObj["textures"]) {
                    std::string name = p.value("name", "");
                    std::string txtPath = p.value("path", "");

                    auto texture = Texture::Load(txtPath);
                    result->SetParam(name, texture);
                }
            }

            return result;
        }
    }
}
