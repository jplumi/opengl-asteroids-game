#include "Game.hpp"
#include "Player.hpp"

Player *player;

bool Game::keys[];

Game::~Game()
{
    delete renderer;
    delete player;
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

    glm::vec2 playerPos = glm::vec2(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
    Texture2D shipTex = ResourceManager::LoadTexture2D("ship", "/Users/joaolumi/Documents/cpp/asteroids/resources/ship.png", true);
    player = new Player(shipTex, playerPos);
    player->speed = 150.0f;
    player->thrustTex = ResourceManager::LoadTexture2D("shipThrust", "/Users/joaolumi/Documents/cpp/asteroids/resources/ship_thrust.png", true);
}

void Game::HandleEvents()
{
    glfwPollEvents();
}

void Game::Update(float deltaTime)
{
    player->Update(deltaTime);
}

void Game::Render()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    player->Render(renderer);

    glfwSwapBuffers(window);
}
