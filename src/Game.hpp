#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Enemies/HUD/HudManager.hpp"
#include "Render/Renderer.hpp"
#include "Render/TextRenderer.hpp"

enum class GameState {
    MENU, PLAYING, DEATH
};

class Player;
class EnemiesManager;
class ShotsManager;
class Ufo;

class Game
{
public:
    ~Game();

    GLFWwindow* window;
    Renderer *renderer;
    TextRenderer *textRenderer;

    HudManager *hudManager;

    EnemiesManager* enemiesManager;
    ShotsManager* shotsManager;
    Ufo* ufo;
    
    Player *player;
    int playerLives = 3;

    bool keys[1024];
public:
    void Init();
    void HandleEvents();
    void Update(float deltaTime);
    void Render();
    void PlayerDeath();
    void Quit();

private:
    bool m_playerIsAlive = true;

    float m_playerDeathTime = 1.5f;
    float m_DeathTimePassed = 0.0f;

    GameState m_gameState;
};

