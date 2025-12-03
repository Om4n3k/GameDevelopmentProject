//
// Created by omank on 1.12.2025.
//

#include "Game.h"
#include "TestObject.h"


bool Game::Init() {
    m_Scene.CreateObject<TestObject>("TestObject");
    return true;
}

void Game::Update(const float deltaTime) {
    m_Scene.Update(deltaTime);
}

void Game::Destroy() {
}

