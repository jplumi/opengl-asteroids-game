#pragma once

#include "Entity/Entity.hpp"
#include <map>

#define MAX_ENEMIES 10

class EnemiesManager
{
public:
    EnemiesManager(Game* game);
    ~EnemiesManager();

    void Init();
    void UpdateEnemies(float deltaTime);
    void RenderEnemies(Renderer* renderer);
    void DestroyEnemy(unsigned int id);

    Entity* CheckCollision(Entity* obj) const;

private:
    Game* m_game;

    std::unordered_map<unsigned int, Entity*> m_enemies;
    int m_enemiesIndex = 0;

    const float m_spawnInterval = 1.0f;
    float m_currSpawnTime = 0.0f;

    const int m_asteroidSizeOptions[3] = { 50, 80, 120 };
private:
    void SpawnAsteroid();
};
