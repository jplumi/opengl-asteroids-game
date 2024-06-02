#include "Entity.hpp"

Entity::Entity() {};

Entity::Entity(
        Texture2D texture,
        glm::vec2 position,
        glm::vec2 size,
        float rotation
) : texture(texture), position(position), size(size), rotation(rotation) {}

void Entity::Render(SpriteRenderer *renderer)
{
    renderer->DrawSprite(texture, position, size, rotation);
}