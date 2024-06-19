#include "Game.hpp"

#include "Defs.h"
#include "GLFW/glfw3.h"
#include "ResourceManager/ResourceManager.hpp"
#include "Player/Player.hpp"
#include "Enemies/EnemiesManager.hpp"
#include "Shots/ShotsManager.hpp"

Game::~Game()
{
    delete renderer;
    delete player;
    delete enemiesManager;
    delete shotsManager;
}

void Game::Init()
{
    renderer = new Renderer();
    renderer->InitRenderData();

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
}

void Game::HandleEvents()
{
    glfwPollEvents();
    // if(!m_playerIsAlive && keys[GLFW_KEY_SPACE])
    // {
    //     player->Reset();
    //     m_playerIsAlive = true;
    // }
}

void Game::Update(float deltaTime)
{
    if(m_playerIsAlive)
        player->Update(deltaTime);
    else if(playerLives > 0)
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
    enemiesManager->UpdateEnemies(deltaTime);
    shotsManager->UpdateShots(deltaTime);
}

void Game::Render()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(m_playerIsAlive)
        player->Render(renderer);

    enemiesManager->RenderEnemies(renderer);
    shotsManager->RenderShots(renderer);

    glBindVertexArray(0);
    glfwSwapBuffers(window);
}

void Game::PlayerDeath()
{
    m_playerIsAlive = false;
}

void Game::Quit()
{
   glfwSetWindowShouldClose(window, true);
}

