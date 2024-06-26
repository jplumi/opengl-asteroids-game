#include "Asteroid.hpp"

#include "Enemies/EnemiesManager.hpp"
#include "Util.h"

void Asteroid::Update(float deltaTime)
{
    Entity::Update(deltaTime);
    position += forward * deltaTime * speed;
}

void Asteroid::OnDestroy()
{
    if(size.x > 35)
    {
        EnemiesManager *em = m_game->enemiesManager;
        em->SpawnAsteroid(position, Util::randomDirection(), size.x/2);
        em->SpawnAsteroid(position, Util::randomDirection(), size.x/2);
    }
}

