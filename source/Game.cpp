//
// Created by omank on 1.12.2025.
//

#include "Game.h"
#include "TestObject.h"

bool Game::Init() {
    m_Scene = new eng::Scene();
    auto camera = m_Scene->CreateObject("Camera");
    camera->AddComponent(new eng::CameraComponent());
    camera->SetPosition(glm::vec3(0.0f, 0.0f, 2.0f));

    m_Scene->SetMainCamera(camera);
    m_Scene->CreateObject<TestObject>("TestObject");

    eng::Engine::GetInstance().SetCurrentScene(m_Scene);
    return true;
}

void Game::Update(const float deltaTime) {
    m_Scene->Update(deltaTime);
}

void Game::Destroy() {
}

