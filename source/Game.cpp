//
// Created by omank on 1.12.2025.
//

#include "Game.h"
#include "TestObject.h"
#include "scene/components/PlayerControllerComponent.h"

bool Game::Init() {
    m_Scene = new eng::Scene();
    auto camera = m_Scene->CreateObject("Camera");
    camera->AddComponent(new eng::CameraComponent());
    camera->SetPosition(glm::vec3(0.0f, 0.0f, 2.0f));
    camera->AddComponent(new eng::PlayerControllerComponent());

    m_Scene->SetMainCamera(camera);
    m_Scene->CreateObject<TestObject>("TestObject");


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

    std::vector<float> cubeVertices = {
        0.5f,  0.5f, 0.5f,  1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f,  0.0f, 1.0f, 0.0f,
       -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 1.0f,
       -0.5f,  0.5f, 0.5f,  1.0f, 1.0f, 0.0f,

        0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
       -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
       -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
    };

    std::vector<unsigned int> indicies = {
        // front face
        0, 1, 2,
        0, 2, 3,

        // top face
        4, 5, 1,
        4, 1, 0,

        // right face
        4, 0, 3,
        4, 3, 7,

        // left face
        1, 5, 6,
        1, 6, 2,

        // bottom face
        3, 2, 6,
        3, 6, 7,

        // back face
        4, 7, 6,
        4, 6, 5
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
        cubeVertices,
        indicies
    );

    material->SetShaderProgram(shaderProgram);

    auto objectA = m_Scene->CreateObject("Object A");
    objectA->AddComponent(new eng::MeshComponent(material, mesh));
    objectA->SetPosition(glm::vec3(0.0f, 2.0f, 0.0f));

    auto objectB = m_Scene->CreateObject("Object B");
    objectB->AddComponent(new eng::MeshComponent(material, mesh));
    objectB->SetPosition(glm::vec3(2.0f, 0.0f, 2.0f));
    objectB->SetRotation(glm::vec3(0.0f, 2.0f, 0.0f));

    auto objectC = m_Scene->CreateObject("Object C");
    objectC->AddComponent(new eng::MeshComponent(material, mesh));
    objectC->SetPosition(glm::vec3(-2.0f, 0.0f, -2.0f));
    objectC->SetScale(glm::vec3(1.5f, 1.5f, 1.5f));


    eng::Engine::GetInstance().SetCurrentScene(m_Scene);
    return true;
}

void Game::Update(const float deltaTime) {
    m_Scene->Update(deltaTime);
}

void Game::Destroy() {
}

