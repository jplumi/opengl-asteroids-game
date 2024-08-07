#include "Player/Player.hpp"

#include "Enemies/EnemiesManager.hpp"
#include "Enemies/Ufo.hpp"
#include "Shots/ShotsManager.hpp"
#include "Defs.h"
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

void Player::Render(Renderer* renderer)
{
    Entity::Render(renderer);
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

    HandleShoot(deltaTime);
    
    // apply force
    position += m_force * deltaTime;

    // drag
    m_force.x = Util::lerp(m_force.x, 0, deltaTime * 0.75f);
    m_force.y = Util::lerp(m_force.y, 0, deltaTime * 0.75f);

    CheckCollision();
}

void Player::UpdateVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(rotation));
    front.y = sin(glm::radians(rotation));
    front.z = 0.0f;

    forward = glm::normalize(front);
}

void Player::RenderThrust(Renderer* renderer)
{
    glm::vec2 thrustPos = position - forward * 11.5f;
    renderer->RenderTexture2D(thrustTex, thrustPos, size, rotation);
}

void Player::CheckCollision()
{
    if(m_game->enemiesManager->CheckCollision(this) != nullptr || m_game->ufo->CheckCollision(this))
        m_game->PlayerDeath();
}

void Player::Reset()
{
    position = glm::vec2(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
    rotation = -90;
    forward = glm::vec2(0.0f, -1.0f);
    m_force = glm::vec2(0.0f);
}

void Player::HandleShoot(float deltaTime)
{
    if(m_canShoot && m_game->keys[GLFW_KEY_SPACE])
    {
        m_game->shotsManager->SpawnShot(ShotType::PLAYER, position, forward);
        m_canShoot = false;
    }

    if(!m_canShoot)
    {
        m_shootPassedTime += deltaTime;
        if(m_shootPassedTime >= m_shootInterval)
        {
            m_canShoot = true;
            m_shootPassedTime = 0.0f;
        }
    }
}

