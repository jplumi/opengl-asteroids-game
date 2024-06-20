#pragma once

#include <Entity/Entity.hpp>

class Player : public Entity
{
public:
    Texture2D* thrustTex;
public:
    using Entity::Entity;

    void AddForce(glm::vec2 f);
    void Rotate(float angle);
    void Reset();

    void Update(float deltaTime) override;
    void Render(Renderer* renderer) override;

private:
    glm::vec2 m_force;

    const float m_thrustFlickTime = 0.02f;
    float m_thrustCurrTime = 0.0f;
    bool m_showThrust = false;

    bool m_canShoot = true;
    float m_shootInterval = 0.2f;
    float m_shootPassedTime = 0.0f;
private:
    void UpdateVectors();
    void RenderThrust(Renderer* renderer);
    void CheckCollision();
    void HandleShoot(float deltaTime);
};
