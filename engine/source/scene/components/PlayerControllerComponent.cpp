//
// Created by omank on 6.12.2025.
//

#include "PlayerControllerComponent.h"
#include "Engine.h"
#include "glm/ext/matrix_transform.hpp"
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
            rotation.y -= deltaX * m_Sensitivity * deltaTime;

            // rot around X axis
            rotation.x -= deltaY * m_Sensitivity * deltaTime;

            m_Owner->SetRotation(rotation);
        }

        glm::mat4 rotMat(1.0f);
        rotMat = glm::rotate(rotMat, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f)); // X-Axis
        rotMat = glm::rotate(rotMat, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f)); // Y-Axis
        rotMat = glm::rotate(rotMat, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f)); // Z-Axis

        glm::vec3 front = glm::normalize(glm::vec3(rotMat * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f)));
        glm::vec3 right = glm::normalize(glm::vec3(rotMat * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f)));
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