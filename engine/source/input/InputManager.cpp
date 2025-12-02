//
// Created by omank on 1.12.2025.
//

#include "InputManager.h"

namespace eng {
    void InputManager::SetKeyPressed(int key, bool pressed) {
        if (key < 0 || key >= static_cast<int>(m_Keys.size())) {
            return;
        }
        m_Keys[key] = pressed;
    }

    bool InputManager::IsKeyPressed(int key) {
        if (key < 0 || key >= static_cast<int>(m_Keys.size())) {
            return false;
        }
        return m_Keys[key];
    }
}