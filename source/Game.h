//
// Created by omank on 1.12.2025.
//
#include <eng.h>
class Game: public eng::Application {
public:
    bool Init() override;
    void Update(float deltaTime) override;
    void Destroy() override;
private:
    eng::Material m_Material;
};