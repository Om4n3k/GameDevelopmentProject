//
// Created by omank on 2.12.2025.
//

#include "Scene.h"

#include <algorithm>

#include "components/LightComponent.h"

namespace eng {
    void Scene::Update(float deltaTime) {
        for (auto it = m_GameObjects.begin(); it != m_GameObjects.end();) {
            if ((*it)->IsAlive()) {
                (*it)->Update(deltaTime);
                ++it;
            } else {
                it = m_GameObjects.erase(it);
            }
        }
    }

    void Scene::Clear() {
        m_GameObjects.clear();
    }

    GameObject *Scene::CreateObject(const std::string &name, GameObject *parent) {
        auto obj = new GameObject();
        obj->SetName(name);
        SetParent(obj, parent);
        obj->m_Scene = this;
        return obj;
    }

    bool Scene::SetParent(GameObject *obj, GameObject *parent) {
        bool result = false;
        auto currentParent = obj->GetParent();

        if (parent == nullptr) {
            if (currentParent != nullptr) {
                auto it = std::find_if(
                    currentParent->m_Children.begin(),
                    currentParent->m_Children.end(),
                    [obj](const std::unique_ptr<GameObject> &el) {
                        return el.get() == obj;
                    }
                );
                if (it != currentParent->m_Children.end()) {
                    m_GameObjects.push_back(std::move(*it));
                    obj->m_Parent = nullptr;
                    currentParent->m_Children.erase(it);
                    result = true;
                }
            } else {
                auto it = std::find_if(
                    m_GameObjects.begin(),
                    m_GameObjects.end(),
                    [obj](const std::unique_ptr<GameObject> &el) {
                        return el.get() == obj;
                    }
                );
                if (it == m_GameObjects.end()) {
                    std::unique_ptr<GameObject> objHolder(obj);
                    m_GameObjects.push_back(std::move(objHolder));
                    result = true;
                }
            }
        } else {
            if (currentParent != nullptr) {
                auto it = std::find_if(
                    currentParent->m_Children.begin(),
                    currentParent->m_Children.end(),
                    [obj](const std::unique_ptr<GameObject> &el) {
                        return el.get() == obj;
                    }
                );

                if (it != currentParent->m_Children.end()) {
                    bool found = false;
                    auto currentElement = parent;
                    while (currentElement) {
                        if (currentParent == obj) {
                            found = true;
                            break;
                        }
                        currentElement = currentElement->GetParent();
                    }

                    if (!found) {
                        parent->m_Children.push_back(std::move(*it));
                        obj->m_Parent = parent;
                        currentParent->m_Children.erase(it);
                        result = true;
                    }
                }
            } else {
                auto it = std::find_if(
                    m_GameObjects.begin(),
                    m_GameObjects.end(),
                    [obj](const std::unique_ptr<GameObject> &el) {
                        return el.get() == obj;
                    }
                );

                if (it == m_GameObjects.end()) {
                    std::unique_ptr<GameObject> objHolder(obj);
                    parent->m_Children.push_back(std::move(objHolder));
                    obj->m_Parent = parent;
                    result = true;
                } else {
                    bool found = false;
                    auto currentElement = parent;
                    while (currentElement) {
                        if (currentParent == obj) {
                            found = true;
                            break;
                        }
                        currentElement = currentElement->GetParent();
                    }
                    if (!found) {
                        parent->m_Children.push_back(std::move(*it));
                        obj->m_Parent = parent;
                        m_GameObjects.erase(it);
                        result = true;
                    }
                }
            }
        }
        return result;
    }

    void Scene::SetMainCamera(GameObject *camera) {
        m_MainCamera = camera;
    }

    GameObject * Scene::GetMainCamera() const {
        return m_MainCamera;
    }

    std::vector<LightData> Scene::CollectLights() {
        std::vector<LightData> lights;
        for (auto& obj : m_GameObjects) {
            CollectLightsRecursive(obj.get(), lights);
        }
        return lights;
    }

    void Scene::CollectLightsRecursive(GameObject *obj, std::vector<LightData> &out) {
        if (const auto light = obj->GetComponent<LightComponent>()) {
            LightData data{};
            data.color = light->GetColor();
            data.position = obj->GetWorldPosition();
            out.push_back(data);
        }

        for (auto& child : obj->m_Children) {
            CollectLightsRecursive(child.get(), out);
        }
    }
} // eng
