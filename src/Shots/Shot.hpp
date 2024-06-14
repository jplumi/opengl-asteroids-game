#pragma once

#include "Entity/Entity.hpp"

enum ShotType
{
    ENEMY, PLAYER
};

class Shot : public Entity
{
public:
    ShotType type;
    void Update(float deltaTime) override;
    void Render(Renderer* renderer) override;
public:
    using Entity::Entity;

private:
    const float m_lifeTime = 1.0f;
    float m_timePassed = 0.0f;
};