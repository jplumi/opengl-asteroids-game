#pragma once

#include "Game.hpp"

class Entity
{
public:
    unsigned int id;

    Entity(Game* game);
    virtual ~Entity() = default;
public:
    Texture2D* texture;
    glm::vec2 position;
    glm::vec2 size;
    float rotation;
    float speed;
    glm::vec2 forward = glm::vec2(1.0f, 0.0f);
    float colliderRadius;
public:
    virtual void Render(Renderer *renderer);
    virtual void Update(float deltaTime);
protected:
    Game* m_game;
    static unsigned int m_idCount;
};