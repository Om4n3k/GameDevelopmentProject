//
// Created by omank on 5.12.2025.
//

#include "CameraComponent.h"

#include "glm/ext/matrix_clip_space.hpp"
#include "scene/GameObject.h"

namespace eng {
    void CameraComponent::Update(float deltaTime) {

    }

    glm::mat4 CameraComponent::GetViewMatrix() const {
        return glm::inverse(m_Owner->GetWorldTransform());
    }

    glm::mat4 CameraComponent::GetProjectionMatrix(float aspect) const {
        return glm::perspective(glm::radians(m_FOV), aspect, m_NearPlane, m_FarPlane);
    }
} // eng