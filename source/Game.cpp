//
// Created by omank on 1.12.2025.
//

#include "Game.h"
#include "TestObject.h"
#include "graphics/Texture.h"
#include "scene/components/PlayerControllerComponent.h"

bool Game::Init() {
    m_Scene = new eng::Scene();
    eng::Engine::GetInstance().SetCurrentScene(m_Scene);

    auto camera = m_Scene->CreateObject("Camera");
    camera->AddComponent(new eng::CameraComponent());
    camera->SetPosition(glm::vec3(0.0f, 0.0f, 2.0f));
    camera->AddComponent(new eng::PlayerControllerComponent());

    m_Scene->SetMainCamera(camera);
    m_Scene->CreateObject<TestObject>("TestObject");

    auto material = eng::Material::Load("materials/brick.json");

    auto mesh = eng::Mesh::CreateCube();

    auto objectA = m_Scene->CreateObject("Object A");
    objectA->AddComponent(new eng::MeshComponent(material, mesh));
    objectA->SetPosition(glm::vec3(1.0f, 0.0f, 5.0f));

    auto objectB = m_Scene->CreateObject("Object B");
    objectB->AddComponent(new eng::MeshComponent(material, mesh));
    objectB->SetPosition(glm::vec3(2.0f, 0.0f, 2.0f));
    objectB->SetRotation(glm::vec3(2.0f, 2.0f, 0.0f));

    auto objectC = m_Scene->CreateObject("Object C");
    objectC->AddComponent(new eng::MeshComponent(material, mesh));
    objectC->SetPosition(glm::vec3(-2.0f, 0.0f, -2.0f));
    objectC->SetScale(glm::vec3(1.5f, 1.5f, 1.5f));

    //auto suzanneMesh = eng::Mesh::Load("models/Suzanne.gltf");
    //auto suzanneMaterial = eng::Material::Load("materials/suzanne.json");

    //auto suzanneObject = m_Scene->CreateObject("Suzanne");
    //suzanneObject->AddComponent(new eng::MeshComponent(suzanneMaterial, suzanneMesh));
    //suzanneObject->SetPosition(glm::vec3(0.0f, 0.0f, -5.0f));

    auto suzanneObject = eng::GameObject::LoadGLTF("models/Suzanne.gltf", "Suzanne");

    auto light = m_Scene->CreateObject("Light");
    auto lightComponent = new eng::LightComponent();
    lightComponent->SetColor(glm::vec3(1.0f));
    light->AddComponent(lightComponent);
    light->SetPosition(glm::vec3(0.0f, 5.0f, 0.0f));
    return true;
}

void Game::Update(const float deltaTime) {
    m_Scene->Update(deltaTime);
}

void Game::Destroy() {
}
