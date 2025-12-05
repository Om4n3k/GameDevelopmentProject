//
// Created by omank on 2.12.2025.
//

#pragma once
#include <vector>
#include <string>
#include <memory>
#include "GameObject.h"

namespace eng {
    class GameObject;
    class Scene {
    public:
        void Update(float deltaTime);
        void Clear();

        GameObject* CreateObject(const std::string& name, GameObject* parent = nullptr);

        template <typename T, typename = std::enable_if_t<std::is_base_of_v<GameObject, T>>>
        T* CreateObject(const std::string& name, GameObject* parent = nullptr) {
            auto obj = new T();
            obj->SetName(name);
            SetParent(obj, parent);
            return obj;
        }

        bool SetParent(GameObject* obj, GameObject* parent);

        void SetMainCamera(GameObject* camera);
        GameObject* GetMainCamera() const;
    private:
        std::vector<std::unique_ptr<GameObject>> m_GameObjects;
        GameObject* m_MainCamera = nullptr;
    };
} // eng