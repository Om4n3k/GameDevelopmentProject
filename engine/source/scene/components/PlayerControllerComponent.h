//
// Created by omank on 6.12.2025.
//

#ifndef GAMEDEVELOPMENTPROJECT_PLAYERCONTROLLERCOMPONENT_H
#define GAMEDEVELOPMENTPROJECT_PLAYERCONTROLLERCOMPONENT_H
#include "scene/Component.h"

namespace eng {
    class PlayerControllerComponent final : public Component {
        COMPONENT(PlayerControllerComponent)
    public:
        void Update(float deltaTime) override;
    private:
        float m_Sensitivity = 0.5f;
        float m_Speed = 1.5f;
    };
} // eng

#endif //GAMEDEVELOPMENTPROJECT_PLAYERCONTROLLERCOMPONENT_H