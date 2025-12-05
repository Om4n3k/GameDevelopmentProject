//
// Created by omank on 4.12.2025.
//

#ifndef GAMEDEVELOPMENTPROJECT_COMPONENT_H
#define GAMEDEVELOPMENTPROJECT_COMPONENT_H

namespace eng {
    class GameObject;
    class Component {
    public:
        virtual ~Component() = default;
        virtual void Update(float deltaTime) = 0;

        GameObject* GetOwner() const;

    protected:
        GameObject* m_Owner = nullptr;
        friend class GameObject;
    };
} // eng

#endif //GAMEDEVELOPMENTPROJECT_COMPONENT_H