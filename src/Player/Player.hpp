#pragma once

#include <Entity/Entity.hpp>

class Player : public Entity
{
public:
    Texture2D thrustTex;
public:
    using Entity::Entity;

    void AddForce(glm::vec2 f);
    void Rotate(float angle);

    void Render(SpriteRenderer* renderer) override;
    void Update(float deltaTime) override;

private:
    glm::vec2 m_force;

    const float m_thrustFlickTime = 0.02f;
    float m_thrustCurrTime = 0.0f;
    bool m_showThrust = false;
private:
    void UpdateVectors();
    void RenderThrust(SpriteRenderer* renderer);
    bool CheckCollision();
};