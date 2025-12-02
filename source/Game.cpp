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

    std::vector<float> rectVerticies = {
        0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom right
       -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  // bottom left
       -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f   // top left
    };

    std::vector<unsigned int> indicies = {
        0, 1, 2,
        0, 2, 3
    };

    eng::VertexLayout vertexLayout;
    vertexLayout.elements.push_back({
        0,
        3,
        GL_FLOAT,
        0
    });
    vertexLayout.elements.push_back({
       1,
        3,
        GL_FLOAT,
        sizeof(float) * 3,
    });
    vertexLayout.stride = sizeof(float) * 6;

    m_Mesh = std::make_unique<eng::Mesh>(
        vertexLayout,
        rectVerticies,
        indicies
    );

    m_Material.SetShaderProgram(shaderProgram);
    return true;
}

void Game::Update(const float deltaTime) {
    auto& input = eng::Engine::GetInstance().GetInputManager();

    if (input.IsKeyPressed(GLFW_KEY_A)) {
        std::cout << "[A] button is pressed" << std::endl;
    }

    eng::RenderCommand renderCommand;
    renderCommand.material = &m_Material;
    renderCommand.mesh = m_Mesh.get();

    auto& renderQueue = eng::Engine::GetInstance().GetRenderQueue();
    renderQueue.Submit(renderCommand);
}

void Game::Destroy() {
}

