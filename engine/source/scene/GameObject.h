//
// Created by omank on 2.12.2025.
//

#pragma once
#include <string>
#include <vector>
#include <memory>

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
    protected:
        GameObject() = default;
    private:
        std::string m_Name;
        GameObject* m_Parent = nullptr;
        std::vector<std::unique_ptr<GameObject>> m_Children;
        bool m_IsAlive = true;

        friend class Scene;
    };
}