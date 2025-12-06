//
// Created by omank on 5.12.2025.
//

#include "CameraComponent.h"

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/gtc/quaternion.hpp"
#include "scene/GameObject.h"

namespace eng {
    void CameraComponent::Update(float deltaTime) {

    }

    glm::mat4 CameraComponent::GetViewMatrix() const {
        glm::mat4 mat = glm::mat4(1.0f);
        mat = glm::mat4_cast(m_Owner->GetRotation());

        mat = glm::translate(mat, m_Owner->GetPosition());
        mat[3] = glm::vec4(m_Owner->GetPosition(), 1.0f);

        if (m_Owner->GetParent()) {
            mat = m_Owner->GetParent()->GetWorldTransform() * mat;
        }
        return glm::inverse(mat);
    }

    glm::mat4 CameraComponent::GetProjectionMatrix(float aspect) const {
        return glm::perspective(glm::radians(m_FOV), aspect, m_NearPlane, m_FarPlane);
    }
} // eng