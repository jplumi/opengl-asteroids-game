#pragma once

#include "Entity/Entity.hpp"
#include "Render/Renderer.hpp"

class Ufo : public Entity
{
public:
    using Entity::Entity;
public:
    void Init();
    void Update(float deltaTime) override;
    void Render(Renderer *renderer) override;

    bool CheckCollision(Entity* e);

    void Die();
private:
    // movement
    float m_switchMovementTime = 2.0f; // random time for the ship to switch y velocity 
    float m_moveTimePassed = 0.0f; // time counter
    float m_yDirections[3] = {-0.5f, 0.0f, 0.5f}; 

    // spawn
    float m_timeToSpawn = 2.0f; // random time for a ship to appear
    float m_spawnTimePassed = 0.0f;
    bool m_shipDied = false;
    bool m_showShip = false;

    // shooting
    float m_timeToShoot= 1.0f;
    float m_timeToShootPassed = 0.0f;

private:
    void Shoot();

    void MoveShip(float deltaTime);
    void CheckShouldShowShip(float deltaTime);

    void ResetShip();
};

