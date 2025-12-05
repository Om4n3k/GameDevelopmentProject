//
// Created by omank on 4.12.2025.
//

#include "Component.h"

namespace eng {
    GameObject * Component::GetOwner() const {
        return m_Owner;
    }
} // eng