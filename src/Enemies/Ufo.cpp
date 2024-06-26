#include "Ufo.hpp"

#include "ResourceManager/ResourceManager.hpp"
#include "Shots/Shot.hpp"
#include "Shots/ShotsManager.hpp"
#include "Util.h"
#include "Defs.h"

void Ufo::Init()
{
    texture = ResourceManager::LoadTexture2D("Ufo", "/Users/joaolumi/Documents/cpp/asteroids/resources/sprites/ufo.png", true);
    speed = 100;
    ResetShip();
}

void Ufo::Update(float deltaTime)
{
    CheckShouldShowShip(deltaTime);
    if(m_showShip)
    {
        MoveShip(deltaTime);
        // shoot
        m_timeToShootPassed += deltaTime;
        if(m_timeToShootPassed >= m_timeToShoot)
        {
            m_timeToShootPassed = 0.0f;
            m_timeToShoot = (100 + rand() % 100) / 100.0f; // from 1.0 to 2.0
            Shoot();
        }
    }
}

void Ufo::MoveShip(float deltaTime)
{
    Entity::Update(deltaTime);
    position += forward * speed * deltaTime;
    m_timePassed += deltaTime;
    if(m_timePassed >= m_switchMovementTime)
    {
        forward.y = m_yDirections[rand() % 3];
        m_timePassed = 0.0f;
    }
}

void Ufo::CheckShouldShowShip(float deltaTime)
{
    if(!m_showShip)
    {
        m_timePassed += deltaTime;
        if(m_timePassed >= m_timeToSpawn)
        {
            // spawn ship
            m_timePassed = 0.0f;
            m_showShip = true;
            ResetShip();
        }
    }
    else if(m_shipDied) 
    {
        m_shipDied = false;
        m_showShip = false;
        m_timePassed = 0.0f;
    }
}


bool Ufo::CheckCollision(Entity* e)
{
    return Util::checkCircleCollision(position, colliderRadius, e->position, e->colliderRadius);
}

void Ufo::Die()
{
    m_shipDied = true;
}

void Ufo::Render(Renderer *renderer)
{
    if(m_showShip)
        Entity::Render(renderer);
}

void Ufo::Shoot()
{
    glm::vec2 direction = glm::normalize(glm::vec2(rand() - RAND_MAX/2, rand() - RAND_MAX/2));
    m_game->shotsManager->SpawnShot(ShotType::ENEMY, position, direction);
}

void Ufo::ResetShip()
{
    if(rand() % 2) // right side
    {
        position.x = WINDOW_WIDTH;
        position.y = rand() % WINDOW_HEIGHT;
        forward = glm::vec2(-1, 0);
    } else // left side
    {
        position.x = 0;
        position.y = rand() % WINDOW_HEIGHT;
        forward = glm::vec2(1, 0);
    }

    size = glm::vec2(60);
    colliderRadius = 30; 
}

