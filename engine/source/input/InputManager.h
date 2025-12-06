//
// Created by omank on 1.12.2025.
//

#pragma once
#include <array>
#include "glm/vec2.hpp"

namespace eng {
    class InputManager {
    private:
        InputManager() = default;
        InputManager(const InputManager&) = delete;
        InputManager(InputManager&&) = delete;
        InputManager& operator=(const InputManager&) = delete;
        InputManager& operator=(InputManager&&) = delete;

    public:
        void SetKeyPressed(int key, bool pressed);
        bool IsKeyPressed(int key) const;

        void SetMouseButtonPressed(int button, bool pressed);
        bool IsMouseButtonPressed(int button) const;

        void SetMousePositionLastFrame(float x, float y);
        glm::vec2 GetMousePositionLastFrame() const;

        void SetMousePosition(float x, float y);
        glm::vec2 GetMousePosition() const;

    private:
        std::array<bool, 256> m_Keys = { false };
        std::array<bool, 16> m_MouseButtons = { false };

        glm::vec2 m_MousePositionLastFrame = glm::vec2(0.0f);
        glm::vec2 m_MousePosition = glm::vec2(0.0f);

        friend class Engine;

    };
}
