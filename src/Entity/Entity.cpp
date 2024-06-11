#include "Entity.hpp"

#include "Defs.h"

Entity::Entity(Game* game) : m_game(game) {}

void Entity::Render(Renderer *renderer)
{
    renderer->RenderTexture2D(texture, position, size, rotation);
}

void Entity::Update(float deltaTime)
{
    if(position.x < -size.x)
        position.x += WINDOW_WIDTH + size.x;
    if(position.x > WINDOW_WIDTH)
        position.x -= WINDOW_WIDTH + size.x;
    if(position.y > WINDOW_HEIGHT)
        position.y -= WINDOW_HEIGHT+size.y;
    if(position.y < -size.y)
        position.y += WINDOW_HEIGHT + size.y;
}

