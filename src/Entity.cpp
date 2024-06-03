#include "Entity.hpp"
#include <iostream>

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

void Entity::MoveForward(float deltaTime)
{
    position += m_forward * speed * deltaTime;
}

void Entity::Rotate(float angle)
{
    rotation += angle;
    UpdateVectors();
}

void Entity::UpdateVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(rotation));
    front.y = sin(glm::radians(rotation));
    front.z = 0.0f;

    m_forward = glm::normalize(front);
    m_up = glm::normalize(glm::cross(front, glm::vec3(0.0f, 0.0f, 1.0f)));
}
