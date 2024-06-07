#include "Player/Player.hpp"

#include "Enemies/EnemiesManager.hpp"
#include "Util.h"

void Player::AddForce(glm::vec2 f)
{
    m_force += f;
}

void Player::Rotate(float angle)
{
    rotation += angle;
    UpdateVectors();
}

void Player::Render(SpriteRenderer* renderer)
{
    renderer->DrawSprite(texture, position, size, rotation);
    if(m_showThrust)
        RenderThrust(renderer);
}

void Player::Update(float deltaTime)
{
    Entity::Update(deltaTime);

    // check input
    if(m_game->keys[GLFW_KEY_W])
    {
        AddForce(forward * deltaTime * speed);
        // thrust flickering efffect
        m_thrustCurrTime += deltaTime;
        if(m_thrustCurrTime >= m_thrustFlickTime)
        {
            m_showThrust = !m_showThrust;
            m_thrustCurrTime = 0.0f;
        }
    } else
    {
        m_showThrust = false;
    }
    if(m_game->keys[GLFW_KEY_A])
        Rotate(-275 * deltaTime);
    if(m_game->keys[GLFW_KEY_D])
        Rotate(275 * deltaTime);
    
    // apply force
    position += m_force * deltaTime;

    // drag
    m_force.x = lerp(m_force.x, 0, deltaTime * 0.75f);
    m_force.y = lerp(m_force.y, 0, deltaTime * 0.75f);
}

void Player::UpdateVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(rotation));
    front.y = sin(glm::radians(rotation));
    front.z = 0.0f;

    forward = glm::normalize(front);
}

void Player::RenderThrust(SpriteRenderer* renderer)
{
    glm::vec2 thrustPos = position - forward * 11.5f;
    renderer->DrawSprite(thrustTex, thrustPos, size, rotation);
}

bool Player::CheckCollision()
{
    // for(Entity* e : )
    return false;
}