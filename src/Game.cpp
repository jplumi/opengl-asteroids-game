#include "Game.hpp"

#include "Defs.h"
#include "ResourceManager/ResourceManager.hpp"
#include "Player/Player.hpp"
#include "Enemies/EnemiesManager.hpp"

Game::~Game()
{
    delete renderer;
    delete player;
    delete enemiesManager;
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
    player->colliderRadius = playerSize/2;
    player->Rotate(-90);
    player->speed = 500.0f;
    player->thrustTex = ResourceManager::LoadTexture2D("shipThrust", "/Users/joaolumi/Documents/cpp/asteroids/resources/sprites/ship_thrust.png", true);

    enemiesManager = new EnemiesManager(this);
    enemiesManager->Init();
}

void Game::HandleEvents()
{
    glfwPollEvents();
    if(!m_playerIsAlive && keys[GLFW_KEY_SPACE])
    {
        player->Reset();
        m_playerIsAlive = true;
    }
}

void Game::Update(float deltaTime)
{
    if(m_playerIsAlive)
        player->Update(deltaTime);
    enemiesManager->UpdateEnemies(deltaTime);
}

void Game::Render()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(m_playerIsAlive)
        player->Render(renderer);

    enemiesManager->RenderEnemies(renderer);

    glBindVertexArray(0);
    glfwSwapBuffers(window);
}

void Game::PlayerDeath()
{
    m_playerIsAlive = false;
}

