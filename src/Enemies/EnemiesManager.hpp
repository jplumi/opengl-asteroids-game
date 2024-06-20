#pragma once

#include "Enemies/Enemy.hpp"
#include <unordered_map>

class EnemiesManager {
public:
  EnemiesManager(Game *game);
  ~EnemiesManager();

  void Init();
  void UpdateEnemies(float deltaTime);
  void RenderEnemies(Renderer *renderer);
  void DestroyEnemy(unsigned int id);

  Entity *CheckCollision(Entity *obj) const;

  void SpawnAsteroid(glm::vec2 position, glm::vec2 direction,
          float size);
private:
  Game *m_game;

  int m_maxEnemies = 6;
  int m_maxSpeed = 200;

  std::unordered_map<unsigned int, Enemy *> m_enemies;

  const float m_spawnInterval = 1.0f;
  float m_currSpawnTime = 0.0f;

private:
  void SpawnRandomAsteroids();
};
