//
// Created by omank on 1.12.2025.
//

#include "Game.h"
#include <iostream>
#include "GLFW/glfw3.h"

bool Game::Init() {
    std::string vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        layout (location = 1) in vec3 aColor;

        out vec3 vColor;

        void main() {
            vColor = aColor;
            gl_Position = vec4(aPos, 1.0);
        }
    )";

    std::string fragmentShaderSource = R"(
        #version 330 core
        out vec4 FragColor;

        in vec3 vColor;

        void main() {
            FragColor = vec4(vColor, 1.0);
        }
    )";

    auto& graphicsApi = eng::Engine::GetInstance().GetGraphicsApi();
    auto shaderProgram = graphicsApi.CreateShaderProgram(vertexShaderSource, fragmentShaderSource);

    m_Material.SetShaderProgram(shaderProgram);
    return true;
}

void Game::Update(const float deltaTime) {
    auto& input = eng::Engine::GetInstance().GetInputManager();
    if (input.IsKeyPressed(GLFW_KEY_A)) {
        std::cout << "[A] button is pressed" << std::endl;
    }
}

void Game::Destroy() {
}

