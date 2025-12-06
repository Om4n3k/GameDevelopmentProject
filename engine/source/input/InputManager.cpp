//
// Created by omank on 1.12.2025.
//

#include "InputManager.h"

#include "scene/components/CameraComponent.h"

namespace eng {
    void InputManager::SetKeyPressed(int key, bool pressed) {
        if (key < 0 || key >= static_cast<int>(m_Keys.size())) {
            return;
        }
        m_Keys[key] = pressed;
    }

    bool InputManager::IsKeyPressed(int key) const {
        if (key < 0 || key >= static_cast<int>(m_Keys.size())) {
            return false;
        }
        return m_Keys[key];
    }

    void InputManager::SetMouseButtonPressed(int button, bool pressed) {
        if (button < 0 || button >= static_cast<int>(m_MouseButtons.size())) {
            return;
        }
        m_MouseButtons[button] = pressed;
    }

    bool InputManager::IsMouseButtonPressed(int button) const {
        if (button < 0 || button >= static_cast<int>(m_MouseButtons.size())) {
            return false;
        }
        return m_MouseButtons[button];
    }

    void InputManager::SetMousePositionLastFrame(float x, float y) {
        m_MousePositionLastFrame = glm::vec2(x, y);
    }

    glm::vec2 InputManager::GetMousePositionLastFrame() const {
        return m_MousePositionLastFrame;
    }

    void InputManager::SetMousePosition(float x, float y) {
        m_MousePositionLastFrame = m_MousePosition;
        m_MousePosition = glm::vec2(x, y);
    }

    glm::vec2 InputManager::GetMousePosition() const {
        return m_MousePosition;
    }
}
