#include "Game.hpp"
#include "Player/Player.hpp"
#include "Enemies/EnemiesManager.hpp"

Player *player;
EnemiesManager* enemiesManager;

bool Game::keys[];

Game::~Game()
{
    delete renderer;
    delete player;
    delete enemiesManager;
}

void Game::Init()
{
    Shader baseShader = ResourceManager::LoadShader("baseShader",
        "/Users/joaolumi/Documents/cpp/asteroids/resources/base.vert",
        "/Users/joaolumi/Documents/cpp/asteroids/resources/base.frag");

    glm::mat4 projection = glm::ortho(0.0f, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT, 0.0f, -1.0f, 1.0f);
    baseShader.Use();
    baseShader.SetInt("image", 0);
    baseShader.SetMat4("projection", projection);

    renderer = new SpriteRenderer(baseShader);

    // init player
    glm::vec2 playerPos = glm::vec2(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
    Texture2D shipTex = ResourceManager::LoadTexture2D("ship", "/Users/joaolumi/Documents/cpp/asteroids/resources/ship.png", true);
    player = new Player(shipTex, playerPos);
    player->Rotate(-90);
    player->speed = 250.0f;
    player->thrustTex = ResourceManager::LoadTexture2D("shipThrust", "/Users/joaolumi/Documents/cpp/asteroids/resources/ship_thrust.png", true);

    enemiesManager = new EnemiesManager();
    enemiesManager->Init();
}

void Game::HandleEvents()
{
    glfwPollEvents();
}

void Game::Update(float deltaTime)
{
    player->Update(deltaTime);
    enemiesManager->UpdateEnemies(deltaTime);
}

void Game::Render()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    player->Render(renderer);
    enemiesManager->RenderEnemies(renderer);

    glfwSwapBuffers(window);
}
