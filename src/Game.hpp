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
public:
    void Init();
    void HandleEvents();
    void Update(float deltaTime);
    void Render();
    void PlayerDeath();

private:
    bool m_playerIsAlive = true;
};
