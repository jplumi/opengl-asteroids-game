#pragma once

#include "Texture2D.hpp"
#include "SpriteRenderer.hpp"

class Entity
{
public:
    Entity();
    Entity(
        Texture2D texture,
        glm::vec2 position = glm::vec2(0.0f),
        glm::vec2 size = glm::vec2(50.0f),
        float rotation = 0.0f);

    Texture2D texture;
    glm::vec2 position;
    glm::vec2 size = glm::vec2(50.0f);
    float rotation;
public:
    void Render(SpriteRenderer *renderer);
};