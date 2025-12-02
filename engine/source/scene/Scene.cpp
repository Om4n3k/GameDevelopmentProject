//
// Created by omank on 2.12.2025.
//

#include "Scene.h"

namespace eng {
    void Scene::Update(float deltaTime) {
        for (auto it = m_GameObjects.begin(); it != m_GameObjects.end(); ) {
            if ((*it)->IsAlive()) {
                (*it)->Update(deltaTime);
                ++it;
            }
            else {
                it = m_GameObjects.erase(it);
            }
        }
    }

    void Scene::Clear() {
        m_GameObjects.clear();
    }

    GameObject* Scene::CreateObject(const std::string &name, GameObject *parent) {
        auto obj = new GameObject();
        obj->SetName(name);
        SetParent(obj, parent);
        return obj;
    }

    void Scene::SetParent(GameObject *obj, GameObject *parent) {
        //TODO
    }
} // eng