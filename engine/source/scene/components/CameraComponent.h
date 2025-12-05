//
// Created by omank on 5.12.2025.
//

#ifndef GAMEDEVELOPMENTPROJECT_CAMERACOMPONENT_H
#define GAMEDEVELOPMENTPROJECT_CAMERACOMPONENT_H
#include "glm/mat4x4.hpp"
#include "scene/Component.h"

namespace eng {
    class CameraComponent : public Component {
        COMPONENT(CameraComponent)
    public:
        void Update(float deltaTime) override;

        glm::mat4 GetViewMatrix() const;
        glm::mat4 GetProjectionMatrix(float aspect) const;
    private:
        float m_FOV = 60.0f;
        float m_NearPlane = 0.1f;
        float m_FarPlane = 1000.0f;
    };
} // eng

#endif //GAMEDEVELOPMENTPROJECT_CAMERACOMPONENT_H