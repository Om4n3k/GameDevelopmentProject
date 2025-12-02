//
// Created by omank on 1.12.2025.
//
#include <eng.h>
#include <memory>

class Game: public eng::Application {
public:
    bool Init() override;
    void Update(float deltaTime) override;
    void Destroy() override;
private:
    eng::Material m_Material;
    std::unique_ptr<eng::Mesh> m_Mesh;
    float m_OffsetX = 0.0f;
    float m_OffsetY = 0.0f;
};