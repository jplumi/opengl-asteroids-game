#include <iostream>
#include <glm/glm.hpp>
#include "Game.hpp"
#include "Shader.hpp"
#include "ResourceManager.hpp"

void frameBufferSizeCallback(GLFWwindow* window, int width, int height);

void GLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

Game game;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    game.window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (game.window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(game.window);

    glfwSetFramebufferSizeCallback(game.window, frameBufferSizeCallback);
    glfwSetKeyCallback(game.window, GLFWKeyCallback);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    game.Init();

    float lastFrameTime = 0.0f;
    float deltaTime = 0.0f;
    while(!glfwWindowShouldClose(game.window))
    {
        float currentTime = glfwGetTime();
        deltaTime = currentTime - lastFrameTime;
        lastFrameTime = currentTime;

        game.HandleEvents();
        game.Update(deltaTime);
        game.Render();
    }

    ResourceManager::Clear();

    glfwTerminate();
}

void frameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void GLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(game.window, true);
    if(key >= 0 && key < 1024)
    {
        if(action == GLFW_PRESS)
            game.keys[key] = true;
        else if(action == GLFW_RELEASE)
            game.keys[key] = false;
    }
}

