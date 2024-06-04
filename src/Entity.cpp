#include "Entity.hpp"
#include "Defs.h"

Entity::Entity() {};

Entity::Entity(
        Texture2D texture,
        glm::vec2 position,
        glm::vec2 size,
        float rotation,
        float speed
) : texture(texture), position(position), size(size), rotation(rotation), speed(speed) {}

void Entity::Render(SpriteRenderer *renderer)
{
    renderer->DrawSprite(texture, position, size, rotation);
}

void Entity::Update(float deltaTime)
{
    if(position.x < -WINDOW_WIDTH)
        position.x += WINDOW_WIDTH;
    if(position.x > WINDOW_WIDTH)
        position.x -= WINDOW_WIDTH;
    if(position.y > WINDOW_HEIGHT)
        position.y -= WINDOW_HEIGHT;
    if(position.y < -WINDOW_HEIGHT)
        position.y += WINDOW_HEIGHT;
}

