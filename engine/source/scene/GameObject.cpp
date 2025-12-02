//
// Created by omank on 2.12.2025.
//

#include "GameObject.h"

namespace eng {
    void GameObject::Update(float deltaTime) {
        for (auto it = m_Children.begin(); it != m_Children.end(); ) {
            if ((*it)->IsAlive()) {
                (*it)->Update(deltaTime);
                ++it;
            }
            else {
                it = m_Children.erase(it);
            }
        }
    }

    const std::string &GameObject::GetName() {
        return m_Name;
    }

    void GameObject::SetName(const std::string &name) {
        m_Name = name;
    }

    GameObject* GameObject::GetParent() const {
        return m_Parent;
    }

    bool GameObject::IsAlive() const {
        return m_IsAlive;
    }

    void GameObject::MarkForDestroy() {
        m_IsAlive = false;
    }





}