#pragma once

#include "Shot.hpp"
#include <unordered_map>

class ShotsManager
{
public:
    ShotsManager(Game* game);
    ~ShotsManager();

    void Init();
    void SpawnShot(ShotType type, glm::vec2 position, glm::vec2 direction);
    void DestroyShot(unsigned int id);
    void UpdateShots(float deltaTime);
    void RenderShots(Renderer* renderer);

private:
    std::unordered_map<unsigned int, Shot*> m_shots;
    Game* m_game;
};
