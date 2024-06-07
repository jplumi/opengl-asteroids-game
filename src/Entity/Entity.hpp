#pragma once

#include "Render/Texture2D.hpp"
#include "Render/SpriteRenderer.hpp"

class Entity
{
public:
    Entity();
    Entity(
        Texture2D texture,
        glm::vec2 position = glm::vec2(0.0f),
        glm::vec2 size = glm::vec2(50.0f),
        float rotation = 0.0f,
        float speed = 100.0f);
    virtual ~Entity() = default;
public:
    Texture2D texture;
    glm::vec2 position;
    glm::vec2 size;
    float rotation;
    float speed;
    glm::vec2 forward = glm::vec2(1.0f, 0.0f);
public:
    virtual void Render(SpriteRenderer *renderer);
    virtual void Update(float deltaTime);
private:
};