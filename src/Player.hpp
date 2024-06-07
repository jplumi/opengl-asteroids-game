#pragma once

#include "Entity.hpp"

float lerp(float min, float max, float value);

const float thrustFlickTime = 0.02f;
float thrustCurrTime = 0.0f;
bool showThrust = false;

class Player : public Entity
{
public:
    Texture2D thrustTex;
public:
    using Entity::Entity;

    void AddForce(glm::vec2 f)
    {
        m_force += f;
    }

    void Rotate(float angle)
    {
        rotation += angle;
        UpdateVectors();
    }

    void Render(SpriteRenderer* renderer) override
    {
        renderer->DrawSprite(texture, position, size, rotation);
        if(showThrust)
            RenderThrust(renderer);
    }

    void Update(float deltaTime) override
    {
        Entity::Update(deltaTime);

        // check input
        if(Game::keys[GLFW_KEY_W])
        {
            AddForce(forward * deltaTime * speed);
            // thrust flickering efffect
            thrustCurrTime += deltaTime;
            if(thrustCurrTime >= thrustFlickTime)
            {
                showThrust = !showThrust;
                thrustCurrTime = 0.0f;
            }
        } else
        {
            showThrust = false;
        }
        if(Game::keys[GLFW_KEY_A])
            Rotate(-150 * deltaTime);
        if(Game::keys[GLFW_KEY_D])
            Rotate(150 * deltaTime);
        
        // apply force
        position += m_force * deltaTime;

        // drag
        m_force.x = lerp(m_force.x, 0, deltaTime);
        m_force.y = lerp(m_force.y, 0, deltaTime);
    }

private:
    glm::vec2 m_force;
private:
    void UpdateVectors()
    {
        glm::vec3 front;
        front.x = cos(glm::radians(rotation));
        front.y = sin(glm::radians(rotation));
        front.z = 0.0f;

        forward = glm::normalize(front);
    }

    void RenderThrust(SpriteRenderer* renderer)
    {
        glm::vec2 thrustPos = position - forward * 11.5f;
        renderer->DrawSprite(thrustTex, thrustPos, size, rotation);
    }
};

float lerp(float min, float max, float value)
{
    return min + (max - min) * value;
}