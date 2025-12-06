//
// Created by omank on 6.12.2025.
//

#include "PlayerControllerComponent.h"
#include "Engine.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/quaternion_trigonometric.hpp"
#include "scene/GameObject.h"

namespace eng {
    void PlayerControllerComponent::Update(float deltaTime) {
        auto& inputManager = Engine::GetInstance().GetInputManager();
        auto rotation = m_Owner->GetRotation();

        if (inputManager.IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
            const auto &mousePos = inputManager.GetMousePosition();
            const auto &lastMousePos = inputManager.GetMousePositionLastFrame();

            float deltaX = mousePos.x - lastMousePos.x;
            float deltaY = mousePos.y - lastMousePos.y;

            // rot around Y axis
            float yAngle = -deltaX * m_Sensitivity * deltaTime;
            glm::quat yRot = glm::angleAxis(yAngle, glm::vec3(0.0f, 1.0f, 0.0f));
            // rotation.y -= deltaX * m_Sensitivity * deltaTime;

            // rot around X axis
            float xAngle = -deltaY * m_Sensitivity * deltaTime;
            glm::vec3 right = rotation * glm::vec3(1.0f, 0.0f, 0.0f);
            glm::quat xRot = glm::angleAxis(xAngle, right);
            // rotation.x -= deltaY * m_Sensitivity * deltaTime;

            glm::quat deltaRot = yRot * xRot;
            rotation = glm::normalize(deltaRot * rotation);

            m_Owner->SetRotation(rotation);
        }

        glm::vec3 front = rotation * glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 right = rotation * glm::vec3(1.0f, 0.0f, 0.0f);
        // glm::vec3 up = glm::normalize(glm::vec3(rotMat * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f)));

        auto position = m_Owner->GetPosition();

        if (inputManager.IsKeyPressed(GLFW_KEY_A)) {
            position -= right * m_Speed * deltaTime;
        }
        if (inputManager.IsKeyPressed(GLFW_KEY_D)) {
            position += right * m_Speed * deltaTime;
        }
        if (inputManager.IsKeyPressed(GLFW_KEY_S)) {
            position -= front * m_Speed * deltaTime;
        }
        if (inputManager.IsKeyPressed(GLFW_KEY_W)) {
            position += front * m_Speed * deltaTime;
        }

        m_Owner->SetPosition(position);
    }
} // eng