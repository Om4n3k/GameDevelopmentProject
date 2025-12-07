//
// Created by omank on 1.12.2025.
//

#include "Game.h"
#include "TestObject.h"
#include "graphics/Texture.h"
#include "scene/components/PlayerControllerComponent.h"

bool Game::Init() {
    auto& fs = eng::Engine::GetInstance().GetFileSystem();
    auto texture = eng::Texture::Load("brick.png");

    m_Scene = new eng::Scene();

    auto camera = m_Scene->CreateObject("Camera");
    camera->AddComponent(new eng::CameraComponent());
    camera->SetPosition(glm::vec3(0.0f, 0.0f, 2.0f));
    camera->AddComponent(new eng::PlayerControllerComponent());

    m_Scene->SetMainCamera(camera);
    m_Scene->CreateObject<TestObject>("TestObject");

    const std::string vertexShaderSource = fs.LoadAssetFileText("shaders/vertex.glsl");
    const std::string fragmentShaderSource = fs.LoadAssetFileText("shaders/fragment.glsl");

    auto &graphicsApi = eng::Engine::GetInstance().GetGraphicsApi();
    const auto shaderProgram = graphicsApi.CreateShaderProgram(vertexShaderSource, fragmentShaderSource);

    std::vector<float> cubeVertices = {
        // Front face
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

        // Top face
        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

        // Right face
        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

        // Left face
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

        // Bottom face
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

        // Back face
        -0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f
    };

    std::vector<unsigned int> indicies = {
        // front face
        0, 1, 2,
        0, 2, 3,

        // top face
        4, 5, 6,
        4, 6, 7,

        // right face
        8, 9, 10,
        8, 10, 11,

        // left face
        12, 13, 14,
        12, 14, 15,

        // bottom face
        16, 17, 18,
        16, 18, 19,

        // back face
        20, 21, 22,
        20, 22, 23
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
    vertexLayout.elements.push_back({
        2,
        2,
        GL_FLOAT,
        sizeof(float) * 6,
    });
    vertexLayout.stride = sizeof(float) * 8;

    auto material = std::make_shared<eng::Material>();
    auto mesh = std::make_shared<eng::Mesh>(
        vertexLayout,
        cubeVertices,
        indicies
    );

    material->SetShaderProgram(shaderProgram);
    material->SetParam("brickTxt", texture);

    auto objectA = m_Scene->CreateObject("Object A");
    objectA->AddComponent(new eng::MeshComponent(material, mesh));
    objectA->SetPosition(glm::vec3(0.0f, 2.0f, 0.0f));

    auto objectB = m_Scene->CreateObject("Object B");
    objectB->AddComponent(new eng::MeshComponent(material, mesh));
    objectB->SetPosition(glm::vec3(2.0f, 0.0f, 2.0f));
    objectB->SetRotation(glm::vec3(2.0f, 2.0f, 0.0f));

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
