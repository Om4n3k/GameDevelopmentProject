//
// Created by omank on 19.12.2025.
//

#pragma once
#include "glm/vec3.hpp"
#include "scene/Component.h"

namespace eng {
    class LightComponent : public Component {
        COMPONENT(LightComponent)
    public:
        void Update(float deltaTime) override;

        void SetColor(const glm::vec3& color);
        glm::vec3 GetColor() const;

    private:
        glm::vec3 m_Color = glm::vec3(1.0f);
    };
} // eng