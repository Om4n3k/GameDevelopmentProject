//
// Created by omank on 5.12.2025.
//

#ifndef GAMEDEVELOPMENTPROJECT_MESHCOMPONENT_H
#define GAMEDEVELOPMENTPROJECT_MESHCOMPONENT_H
#include <memory>
#include "scene/Component.h"
namespace eng {
    class Mesh;
    class Material;

    class MeshComponent : public Component {
        COMPONENT(MeshComponent)
    public:
        MeshComponent(const std::shared_ptr<Material> &material, const std::shared_ptr<Mesh> &mesh);
        void Update(float deltaTime) override;
    private:
        std::shared_ptr<Material> m_Material;
        std::shared_ptr<Mesh> m_Mesh;
    };
} // eng

#endif //GAMEDEVELOPMENTPROJECT_MESHCOMPONENT_H