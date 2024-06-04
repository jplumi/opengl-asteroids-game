#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Defs.h"
#include "ResourceManager.hpp"
#include "SpriteRenderer.hpp"

class Game
{
public:
    ~Game();

    GLFWwindow* window;
    SpriteRenderer *renderer;
    static bool keys[1024];
public:
    void Init();
    void HandleEvents();
    void Update(float deltaTime);
    void Render();
};
