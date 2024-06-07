#include "EnemiesManager.hpp"
#include "ResourceManager/ResourceManager.hpp"
#include "Defs.h"

EnemiesManager::EnemiesManager(Game* game) : m_game(game) {}

EnemiesManager::~EnemiesManager()
{
    for(Entity* e : m_enemies)
        delete e;
    m_enemies.clear();
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
        Entity* newEnemy = new Entity(m_game);

        // random sprite
        newEnemy->texture = ResourceManager::GetTexture2D(
            "asteroid" + std::to_string(1 + rand() % 3));

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

        // random rotation
        float randomAngle = rand() % 180;
        newEnemy->rotation = randomAngle;

        // random direction
        newEnemy->forward = glm::normalize(glm::vec2(rand() - RAND_MAX/2, rand() - RAND_MAX/2));

        // random speed
        newEnemy->speed = 20 + rand() % 200;

        m_enemies.push_back(newEnemy);
        m_enemiesIndex++;
    }
}

void EnemiesManager::UpdateEnemies(float deltaTime)
{
    m_currSpawnTime += deltaTime;
    if(m_currSpawnTime >= m_spawnInterval)
    {
        SpawnAsteroid();
        m_currSpawnTime = 0.0f;
    }

    for(Entity* e : m_enemies)
    {
        e->Update(deltaTime);
        e->position += e->forward * deltaTime * e->speed;
    }
}

void EnemiesManager::RenderEnemies(SpriteRenderer* renderer)
{
    for(int i = 0; i < m_enemiesIndex; i++)
    {
        Entity* e = m_enemies[i];
        renderer->DrawSprite(e->texture, e->position, e->size, e->rotation);
    }
}

const std::vector<Entity*>* EnemiesManager::GetEnemies() const { return &m_enemies; }

