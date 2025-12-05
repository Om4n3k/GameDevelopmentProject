//
// Created by omank on 4.12.2025.
//

#ifndef GAMEDEVELOPMENTPROJECT_COMPONENT_H
#define GAMEDEVELOPMENTPROJECT_COMPONENT_H
#include <cstddef>
namespace eng {
    class GameObject;
    class Component {
    public:
        virtual ~Component() = default;
        virtual void Update(float deltaTime) = 0;
        virtual size_t GetTypeId() const;

        GameObject* GetOwner() const;

        template<typename T>
        static size_t StaticTypeId() {
            static size_t typeId = nextId++;
            return typeId;
        }

    protected:
        GameObject* m_Owner = nullptr;
        friend class GameObject;

    private:
        static size_t nextId;
    };

#define COMPONENT(ComponentClass) \
public: \
    static size_t TypeId() {return eng::Component::StaticTypeId<ComponentClass>(); } \
    size_t GetTypeId() const override { return TypeId();}
} // eng

#endif //GAMEDEVELOPMENTPROJECT_COMPONENT_H