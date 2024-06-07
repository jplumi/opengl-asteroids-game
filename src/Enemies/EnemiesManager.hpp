#pragma once

#include "Entity/Entity.hpp"
#include <vector>

#define MAX_ENEMIES 10

class EnemiesManager
{
public:
    EnemiesManager(Game* game);
    ~EnemiesManager();

    void Init();
    void UpdateEnemies(float deltaTime);
    void RenderEnemies(SpriteRenderer* renderer);

    const std::vector<Entity*>* GetEnemies() const;

private:
    Game* m_game;

    std::vector<Entity*> m_enemies;
    int m_enemiesIndex = 0;

    const float m_spawnInterval = 1.0f;
    float m_currSpawnTime = 0.0f;

    const int m_asteroidSizeOptions[3] = { 50, 80, 120 };
private:
    void SpawnAsteroid();
};
