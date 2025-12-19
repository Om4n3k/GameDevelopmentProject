//
// Created by omank on 2.12.2025.
//

#pragma once
#include <vector>
#include <string>
#include <memory>

#include "Common.h"
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
            obj->m_Scene = this;
            return obj;
        }

        bool SetParent(GameObject* obj, GameObject* parent);

        void SetMainCamera(GameObject* camera);
        GameObject* GetMainCamera() const;

        std::vector<LightData> CollectLights();
    private:
        void CollectLightsRecursive(GameObject* obj, std::vector<LightData>& out);
    private:
        std::vector<std::unique_ptr<GameObject>> m_GameObjects;
        GameObject* m_MainCamera = nullptr;
    };
} // eng