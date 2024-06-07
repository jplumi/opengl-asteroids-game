#pragma once

#include "Shader.hpp"
#include "Texture2D.hpp"

class SpriteRenderer
{
public:
    SpriteRenderer(Shader &shader);
    ~SpriteRenderer();

    void DrawSprite(const Texture2D &texture, glm::vec2 position, 
        glm::vec2 size = glm::vec2(50.0f, 50.0f), float rotate = 0.0f, 
        glm::vec3 color = glm::vec3(1.0f)) const;
private:
    Shader _shader; 
    unsigned int _quadVAO;
    unsigned int _EBO;

    void InitRenderData();
};