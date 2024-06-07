#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Render/SpriteRenderer.hpp"

class Player;
class EnemiesManager;

class Game
{
public:
    ~Game();

    GLFWwindow* window;
    SpriteRenderer *renderer;
    Player *player;
    EnemiesManager* enemiesManager;
    bool keys[1024];
public:
    void Init();
    void HandleEvents();
    void Update(float deltaTime);
    void Render();
};
