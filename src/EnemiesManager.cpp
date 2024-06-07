#include "EnemiesManager.hpp"
#include "ResourceManager.hpp"
#include "Defs.h"

EnemiesManager::~EnemiesManager()
{
    for(Entity* e : enemies)
        delete e;
    enemies.clear();
}

void EnemiesManager::Init()
{
    ResourceManager::LoadTexture2D("asteroid1", "/Users/joaolumi/Documents/cpp/asteroids/resources/big_asteroid_1.png", true);
    ResourceManager::LoadTexture2D("asteroid2", "/Users/joaolumi/Documents/cpp/asteroids/resources/big_asteroid_2.png", true);
    ResourceManager::LoadTexture2D("asteroid3", "/Users/joaolumi/Documents/cpp/asteroids/resources/big_asteroid_3.png", true);
    SpawnAsteroid();
}

void EnemiesManager::SpawnAsteroid()
{
    if(m_enemiesIndex < MAX_ENEMIES)
    {
        Entity* newEnemy = new Entity(
            ResourceManager::GetTexture2D("asteroid1"));

        // random size
        int randomSize = m_asteroidSizeOptions[rand() % 3];
        newEnemy->size = glm::vec2(randomSize);

        // random position
        if(rand() % 2) // right side
        {
            newEnemy->position.x = WINDOW_WIDTH;
            newEnemy->position.y = rand() % WINDOW_HEIGHT;
        } else // left side
        {
            newEnemy->position.x = -newEnemy->size.x;
            newEnemy->position.y = rand() % WINDOW_HEIGHT;
        }
        
        std::cout << "spawned at: " << newEnemy->position.x << ", " << newEnemy->position.y << '\n';

        // random direction
        newEnemy->forward = glm::normalize(glm::vec2(rand() % 100, rand() % 100));

        enemies.push_back(newEnemy);
        m_enemiesIndex++;
    }
}

void EnemiesManager::UpdateEnemies(float deltaTime)
{
    // m_currSpawnTime += deltaTime;
    // if(m_currSpawnTime >= m_spawnInterval)
    // {
    //     SpawnAsteroid();
    //     m_currSpawnTime = 0.0f;
    // }

    for(Entity* e : enemies)
    {
        e->Update(deltaTime);
        e->position += e->forward * deltaTime * 100.0f;
        // std::cout << e->position.x << ", " << e->position.y << '\n';
    }
}

void EnemiesManager::RenderEnemies(SpriteRenderer* renderer)
{
    for(int i = 0; i < m_enemiesIndex; i++)
    {
        Entity* e = enemies[i];
        renderer->DrawSprite(e->texture, e->position, e->size, e->rotation);
    }
}
