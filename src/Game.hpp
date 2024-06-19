#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Render/Renderer.hpp"

class Player;
class EnemiesManager;
class ShotsManager;

class Game
{
public:
    ~Game();

    GLFWwindow* window;
    Renderer *renderer;
    Player *player;
    EnemiesManager* enemiesManager;
    ShotsManager* shotsManager;
    bool keys[1024];

    int playerLives = 3;
public:
    void Init();
    void HandleEvents();
    void Update(float deltaTime);
    void Render();
    void PlayerDeath();
    void Quit();

private:
    bool m_playerIsAlive = true;

    float m_playerDeathTime = 1.0f;
    float m_DeathTimePassed = 0.0f;
};
