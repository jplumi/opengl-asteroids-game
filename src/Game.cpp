#include "Game.hpp"

#include "Defs.h"
#include "Enemies/HUD/HudManager.hpp"
#include "GLFW/glfw3.h"
#include "ResourceManager/ResourceManager.hpp"
#include "Player/Player.hpp"
#include "Enemies/EnemiesManager.hpp"
#include "Shots/ShotsManager.hpp"
#include "Enemies/Ufo.hpp"

Game::~Game()
{
    delete renderer;
    delete textRenderer;
    delete player;
    delete enemiesManager;
    delete shotsManager;
    delete ufo;
    delete hudManager;
}

void Game::Init()
{
    renderer = new Renderer();
    renderer->InitRenderData();

    textRenderer = new TextRenderer(WINDOW_WIDTH, WINDOW_HEIGHT);
    textRenderer->Load("/Users/joaolumi/Documents/cpp/asteroids/resources/fonts/hyperspace/Hyperspace.otf", 24);

    // init player
    glm::vec2 playerPos = glm::vec2(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
    int playerSize = 50;

    player = new Player(this);
    player->texture = ResourceManager::LoadTexture2D("ship", "/Users/joaolumi/Documents/cpp/asteroids/resources/sprites/ship.png", true);
    player->position = playerPos;
    player->size = glm::vec2(playerSize);
    player->colliderRadius = playerSize/2.0f;
    player->Rotate(-90);
    player->speed = 500.0f;
    player->thrustTex = ResourceManager::LoadTexture2D("shipThrust", "/Users/joaolumi/Documents/cpp/asteroids/resources/sprites/ship_thrust.png", true);

    enemiesManager = new EnemiesManager(this);
    enemiesManager->Init();

    shotsManager = new ShotsManager(this);
    ufo = new Ufo(this);
    ufo->Init();

    hudManager = new HudManager();

    m_gameState = GameState::MENU;
}

void Game::HandleEvents()
{
    glfwPollEvents();
    if(m_gameState == GameState::MENU)
    {
        if(keys[GLFW_KEY_ENTER])
        {
            enemiesManager->Reset();
            ufo->Reset();
            m_gameState = GameState::PLAYING;
        }
    }
}

void Game::Update(float deltaTime)
{
    if(m_gameState == GameState::MENU)
    {

    }
    else if(m_gameState == GameState::PLAYING)
    {
        if(m_playerIsAlive)
            player->Update(deltaTime);
        else if(playerLives > 1)
        {
            m_DeathTimePassed += deltaTime;
            if(m_DeathTimePassed >= m_playerDeathTime) {
                playerLives--;
                player->Reset();
                m_playerIsAlive = true;
                m_DeathTimePassed = 0.0f;
            }
        }
        else
        {
            Quit();
        }
    }
    enemiesManager->UpdateEnemies(deltaTime);
    ufo->Update(deltaTime);
    shotsManager->UpdateShots(deltaTime);
}

void Game::Render()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(m_gameState == GameState::MENU)
    {
        textRenderer->RenderText("press enter", 325, 300, 1.5f);
    }
    else if(m_gameState == GameState::PLAYING)
    {
        if(m_playerIsAlive)
            player->Render(renderer);
    }
    enemiesManager->RenderEnemies(renderer);
    shotsManager->RenderShots(renderer);
    ufo->Render(renderer);

    hudManager->Render(renderer, textRenderer);

    glfwSwapBuffers(window);
}

void Game::PlayerDeath()
{
    m_playerIsAlive = false;
    hudManager->TakeLife();
}

void Game::Quit()
{
   glfwSetWindowShouldClose(window, true);
}

