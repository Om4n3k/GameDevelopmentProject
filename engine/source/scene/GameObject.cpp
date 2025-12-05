//
// Created by omank on 2.12.2025.
//

#include "GameObject.h"
#include <glm/gtc/matrix_transform.hpp>

#include "Component.h"

namespace eng {
    void GameObject::Update(float deltaTime) {
        for (auto & component : m_Components) {
            component->Update(deltaTime);
        }
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

    void GameObject::AddComponent(Component *component) {
        m_Components.emplace_back(component);
        component->m_Owner = this;
    }

    glm::vec3 GameObject::GetPosition() const {
        return m_Position;
    }

    void GameObject::SetPosition(const glm::vec3 &position) {
        m_Position = position;
    }

    glm::vec3 GameObject::GetRotation() const {
        return m_Rotation;
    }

    void GameObject::SetRotation(const glm::vec3 &rotation) {
        m_Rotation = rotation;
    }

    glm::vec3 GameObject::GetScale() const {
        return m_Scale;
    }

    void GameObject::SetScale(const glm::vec3 &scale) {
        m_Scale = scale;
    }

    glm::mat4 GameObject::GetLocalTransform() const {
        auto mat = glm::mat4(1.0f);

        // Translation
        mat = glm::translate(mat, m_Position);

        // Rotation
        mat = glm::rotate(mat, m_Rotation.x, glm::vec3(1, 0, 0));
        mat = glm::rotate(mat, m_Rotation.y, glm::vec3(0, 1, 0));
        mat = glm::rotate(mat, m_Rotation.z, glm::vec3(0, 0, 1));

        // Scale
        mat = glm::scale(mat, m_Scale);

        return mat;
    }

    glm::mat4 GameObject::GetWorldTransform() const {
        if (m_Parent) {
            return m_Parent->GetWorldTransform() * GetLocalTransform();
        }
        return GetLocalTransform();
    }
}
