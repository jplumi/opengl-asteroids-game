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
        float rotation = 0.0f,
        float speed = 100.0f);

    Texture2D texture;
    glm::vec2 position;
    glm::vec2 size;
    float rotation;
    float speed;

public:
    void Render(SpriteRenderer *renderer);
    void MoveForward(float deltaTime);
    void Rotate(float angle);

private:
    glm::vec2 m_forward = glm::vec2(1.0f, 0.0f);
    glm::vec2 m_up = glm::vec2(0.0f, 1.0f);
private:
    void UpdateVectors();
};