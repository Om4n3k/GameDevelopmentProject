//
// Created by omank on 2.12.2025.
//

#pragma once
#include <string>
#include <vector>
#include <memory>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include "scene/Component.h"

namespace eng {
    class Scene;
    class GameObject {
    public:
        virtual ~GameObject() = default;
        virtual void Update(float deltaTime);
        const std::string& GetName();
        void SetName(const std::string& name);
        GameObject* GetParent() const;
        void SetParent(GameObject* parent);
        bool IsAlive() const;
        void MarkForDestroy();

        void AddComponent(Component* component);
        template<typename T, typename = std::enable_if_t<std::is_base_of_v<Component, T>>>
        T* GetComponent() {
            size_t typeId = Component::StaticTypeId<T>();
            for (auto& component : m_Components) {
                if (component->GetTypeId() == typeId) {
                    return static_cast<T*>(component.get());
                }
            }
            return nullptr;
        }

        glm::vec3 GetPosition() const;
        void SetPosition(const glm::vec3& position);
        glm::vec3 GetRotation() const;
        void SetRotation(const glm::vec3& rotation);
        glm::vec3 GetScale() const;
        void SetScale(const glm::vec3& scale);

        glm::mat4 GetLocalTransform() const;
        glm::mat4 GetWorldTransform() const;
    protected:
        GameObject() = default;
    private:
        std::string m_Name;
        GameObject* m_Parent = nullptr;
        std::vector<std::unique_ptr<GameObject>> m_Children;
        std::vector<std::unique_ptr<Component>> m_Components;
        bool m_IsAlive = true;
        glm::vec3 m_Position = glm::vec3(0.0f);
        glm::vec3 m_Rotation = glm::vec3(0.0f);
        glm::vec3 m_Scale = glm::vec3(1.0f);

        friend class Scene;
    };
}
