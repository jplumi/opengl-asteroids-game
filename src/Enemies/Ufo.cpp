#include "Ufo.hpp"

#include "ResourceManager/ResourceManager.hpp"
#include "Util.h"

void Ufo::Init()
{
    texture = ResourceManager::LoadTexture2D("Ufo", "/Users/joaolumi/Documents/cpp/asteroids/resources/sprites/ufo.png", true);
    position = glm::vec2(0.0f, 400.0f);
    forward = glm::vec2(1, 0);
    speed = 100;

    size = glm::vec2(60);
    colliderRadius = 30;
}

void Ufo::Update(float deltaTime)
{
    CheckShouldShowShip(deltaTime);
    if(m_showShip)
    {
        MoveShip(deltaTime);
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
            m_timePassed = 0.0f;
            m_showShip = true;
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

