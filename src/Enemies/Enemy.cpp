#include "Enemy.hpp"

#include "Enemies/EnemiesManager.hpp"
#include "Util.h"

void Enemy::Update(float deltaTime)
{
    Entity::Update(deltaTime);
    position += forward * deltaTime * speed;
}

void Enemy::OnDestroy()
{
    if(size.x > 35)
    {
        EnemiesManager *em = m_game->enemiesManager;
        em->SpawnAsteroid(position, Util::randomDirection(), size.x/2);
        em->SpawnAsteroid(position, Util::randomDirection(), size.x/2);
    }
}

