#include "EnemiesManager.hpp"
#include "ResourceManager/ResourceManager.hpp"
#include "Defs.h"

bool checkCircleCollision(const glm::vec2 &aPos, float aRadius,
                          const glm::vec2 &bPos, float bRadius);

EnemiesManager::EnemiesManager(Game* game) : m_game(game) {}

EnemiesManager::~EnemiesManager()
{
    for(auto e : m_enemies)
        delete e.second;
    m_enemies.clear();
}

void EnemiesManager::Init()
{
    ResourceManager::LoadTexture2D("asteroid1", "/Users/joaolumi/Documents/cpp/asteroids/resources/sprites/big_asteroid_1.png", true);
    ResourceManager::LoadTexture2D("asteroid2", "/Users/joaolumi/Documents/cpp/asteroids/resources/sprites/big_asteroid_2.png", true);
    ResourceManager::LoadTexture2D("asteroid3", "/Users/joaolumi/Documents/cpp/asteroids/resources/sprites/big_asteroid_3.png", true);
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
        newEnemy->colliderRadius = randomSize/2;

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

        m_enemies.emplace(newEnemy->id, newEnemy);
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

    for(auto it = m_enemies.begin(); it != m_enemies.end();)
    {
        Entity* e = it->second;
        if(e != nullptr)
        {
            e->Update(deltaTime);
            e->position += e->forward * deltaTime * e->speed;
            ++it;
        } 
        else
        {
            it = m_enemies.erase(it);
        }
    }
}

void EnemiesManager::RenderEnemies(Renderer* renderer)
{
    for(auto it = m_enemies.begin(); it != m_enemies.end();)
    {
        if(it->second)
        {
            it->second->Render(renderer);
            ++it;
        }
        else
        {
            it = m_enemies.erase(it);
        }
    }
}

void EnemiesManager::DestroyEnemy(unsigned int id)
{
    auto it = m_enemies.find(id);
    if(it != m_enemies.end())
    {
        delete it->second;
        it->second = nullptr;
    }
}

Entity* EnemiesManager::CheckCollision(Entity* obj) const
{
    for(auto it = m_enemies.begin(); it != m_enemies.end(); ++it)
    {
        if(it->second != nullptr)
        {
            Entity* enemy = it->second;
            if(checkCircleCollision(obj->position, obj->colliderRadius, enemy->position, enemy->colliderRadius))
            {
                return enemy;
            }
        }
    }
    return nullptr;
}


