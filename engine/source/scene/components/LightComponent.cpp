//
// Created by omank on 19.12.2025.
//

#include "LightComponent.h"

namespace eng {
    void LightComponent::Update(float deltaTime) {

    }

    void LightComponent::SetColor(const glm::vec3& color) {
        m_Color = color;
    }

    glm::vec3 LightComponent::GetColor() const {
        return m_Color;
    }
} // eng