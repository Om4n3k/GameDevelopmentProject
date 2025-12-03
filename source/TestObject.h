//
// Created by omank on 3.12.2025.
//

#ifndef GAMEDEVELOPMENTPROJECT_TESTOBJECT_H
#define GAMEDEVELOPMENTPROJECT_TESTOBJECT_H
#include "eng.h"

class TestObject : public eng::GameObject {
public:
    TestObject();

    void Update(float deltaTime) override;
private:
    eng::Material m_Material;
    std::shared_ptr<eng::Mesh> m_Mesh;
};

#endif //GAMEDEVELOPMENTPROJECT_TESTOBJECT_H