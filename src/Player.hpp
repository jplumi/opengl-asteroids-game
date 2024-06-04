#pragma once

#include "Entity.hpp"
#include "Game.hpp"

float magnitude(glm::vec2 vector);
float lerp(float min, float max, float value);


class Player : public Entity
{
public:
    glm::vec2 forward = glm::vec2(1.0f, 0.0f);
    glm::vec2 up = glm::vec2(0.0f, -1.0f);
public:
    using Entity::Entity;

    void AddForce(glm::vec2 f)
    {
        force += f;
    }

    void Rotate(float angle)
    {
        rotation += angle;
        UpdateVectors();
    }

    void Update(float deltaTime) override
    {
         // check input
        if(Game::keys[GLFW_KEY_W])
            AddForce(forward * deltaTime * speed);
        if(Game::keys[GLFW_KEY_A])
            Rotate(-120 * deltaTime);
        if(Game::keys[GLFW_KEY_D])
            Rotate(120 * deltaTime);
        
        // apply force
        position += force * deltaTime;

        // drag
        force.x = lerp(force.x, 0, deltaTime);
        force.y = lerp(force.y, 0, deltaTime);

        std::cout << "force: " << force.x << ", " << force.y << '\n';
    }

private:
    glm::vec2 force;
private:
    void UpdateVectors()
    {
        glm::vec3 front;
        front.x = cos(glm::radians(rotation));
        front.y = sin(glm::radians(rotation));
        front.z = 0.0f;

        forward = glm::normalize(front);
        up = glm::normalize(glm::cross(front, glm::vec3(0.0f, 0.0f, 1.0f)));
    }
};

float magnitude(glm::vec2 vector)
{
    return vector.x * vector.x + vector.y * vector.y;
}

float lerp(float min, float max, float value)
{
    return min + (max - min) * value;
}