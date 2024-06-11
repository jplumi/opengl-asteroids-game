#pragma once

#include "Render/Texture2D.hpp"
#include "Render/Renderer.hpp"
#include "Game.hpp"

class Entity
{
public:
    Entity(Game* game);
    virtual ~Entity() = default;
public:
    Texture2D* texture;
    glm::vec2 position;
    glm::vec2 size;
    float rotation;
    float speed;
    glm::vec2 forward = glm::vec2(1.0f, 0.0f);
public:
    virtual void Render(Renderer *renderer);
    virtual void Update(float deltaTime);
protected:
    Game* m_game;
};