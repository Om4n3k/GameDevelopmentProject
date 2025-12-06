//
// Created by omank on 3.12.2025.
//

#include "TestObject.h"
#include "GLFW/glfw3.h"
#include <iostream>

TestObject::TestObject() {
    std::string vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        layout (location = 1) in vec3 aColor;

        out vec3 vColor;

        uniform mat4 uModel;
        uniform mat4 uView;
        uniform mat4 uProjection;

        void main() {
            vColor = aColor;
            gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);
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

    auto material = std::make_shared<eng::Material>();
    auto mesh = std::make_shared<eng::Mesh>(
        vertexLayout,
        rectVerticies,
        indicies
    );

    material->SetShaderProgram(shaderProgram);

    AddComponent(new eng::MeshComponent(material, mesh));
}

void TestObject::Update(float deltaTime) {
    GameObject::Update(deltaTime);
#if 0
    auto position = GetPosition();
    auto& input = eng::Engine::GetInstance().GetInputManager();

    if (input.IsKeyPressed(GLFW_KEY_A)) {
        position.x -= 0.01f;
    }
    if (input.IsKeyPressed(GLFW_KEY_D)) {
        position.x += 0.01f;
    }
    if (input.IsKeyPressed(GLFW_KEY_S)) {
        position.y -= 0.01f;
    }
    if (input.IsKeyPressed(GLFW_KEY_W)) {
        position.y += 0.01f;
    }

    SetPosition(position);
}
#endif
}
