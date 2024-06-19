#include "EnemiesManager.hpp"
#include "ResourceManager/ResourceManager.hpp"
#include "Defs.h"
#include "Util.h"

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
    SpawnRandomAsteroids();
}

void EnemiesManager::SpawnRandomAsteroids()
{
    for(int i = 0; i < m_maxEnemies; i++)
    {
        float size = 140;

        // random position
        glm::vec2 position;
        if(rand() % 2) // right side
        {
            position.x = WINDOW_WIDTH;
            position.y = rand() % WINDOW_HEIGHT;
        } else // left side
        {
            position.x = 0;
            position.y = rand() % WINDOW_HEIGHT;
        }

        glm::vec2 direction = glm::normalize(glm::vec2(rand() - RAND_MAX/2, rand() - RAND_MAX/2));

        SpawnAsteroid(position, direction, size);
    }
}

void EnemiesManager::SpawnAsteroid(glm::vec2 position, glm::vec2 direction, float size)
{
    Entity* enemy = new Entity(m_game);
    enemy->position = position;
    enemy->forward = direction;
    enemy->speed = (float) m_maxSpeed/10 + rand() % m_maxSpeed;
    
    enemy->size = glm::vec2(size);
    enemy->colliderRadius = size/2;

    enemy->texture = ResourceManager::GetTexture2D(
        "asteroid" + std::to_string(1 + rand() % 3));

    float randomAngle = rand() % 180;
    enemy->rotation = randomAngle;

    m_enemies.emplace(enemy->id, enemy);
}

void EnemiesManager::UpdateEnemies(float deltaTime)
{
    if(m_enemies.size() == 0)
    {
        m_currSpawnTime += deltaTime;
        if(m_currSpawnTime >= m_spawnInterval)
        {
            SpawnRandomAsteroids();
            m_currSpawnTime = 0.0f;
            m_maxEnemies++;
        }
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
        Entity* e = it->second;
        if(e->size.x > 35)
        {
            SpawnAsteroid(e->position, Util::randomDirection(), e->size.x/2);
            SpawnAsteroid(e->position, Util::randomDirection(), e->size.x/2);
        }
        delete e;
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
            if(Util::checkCircleCollision(obj->position, obj->colliderRadius, enemy->position, enemy->colliderRadius))
            {
                return enemy;
            }
        }
    }
    return nullptr;
}


