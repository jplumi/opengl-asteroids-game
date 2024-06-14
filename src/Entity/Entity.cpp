#include "Entity.hpp"

#include "Defs.h"

unsigned int Entity::m_idCount = 0;

Entity::Entity(Game* game) : m_game(game)
{ 
    id = m_idCount++;
}

void Entity::Render(Renderer *renderer)
{
    renderer->RenderTexture2D(texture, position, size, rotation);
    
    // render collider
    // renderer->RenderCircle(
    //     position,
    //     colliderRadius,
    //     glm::vec3(0.0f, 0.8f, 0.0f),
    //     0.01f);
}

void Entity::Update(float deltaTime)
{
    if(position.x < -(size.x/2))
        position.x += WINDOW_WIDTH + size.x;
    if(position.x > WINDOW_WIDTH + size.x/2)
        position.x -= WINDOW_WIDTH + size.x;
    if(position.y > WINDOW_HEIGHT + size.y/2)
        position.y -= WINDOW_HEIGHT+size.y;
    if(position.y < -(size.y/2))
        position.y += WINDOW_HEIGHT + size.y;
}

