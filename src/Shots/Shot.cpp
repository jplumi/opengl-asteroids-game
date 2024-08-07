#include "Shot.hpp"

#include "Player/Player.hpp"
#include "ShotsManager.hpp"
#include "Enemies/EnemiesManager.hpp"
#include "Enemies/Ufo.hpp"
#include "Util.h"

void Shot::Update(float deltaTime)
{
    Entity::Update(deltaTime);

    position += forward * speed * deltaTime;

    if(type == ShotType::PLAYER)
    {
        Entity* enemy = m_game->enemiesManager->CheckCollision(this);
        if(enemy != nullptr)
        {
            switch ((int)enemy->size.x) {
                case 35:
                    m_game->hudManager->AddPoints(100);
                    break;
                case 70:
                    m_game->hudManager->AddPoints(50);
                    break;
                case 140:
                    m_game->hudManager->AddPoints(20);
                    break;
                default: 
                    break;

            }
            m_game->enemiesManager->DestroyEnemy(enemy->id);
            m_game->shotsManager->DestroyShot(id);
            return;
        }

        if(m_game->ufo->CheckCollision(this))
        {
            m_game->ufo->Die();
            m_game->hudManager->AddPoints(200);
            m_game->shotsManager->DestroyShot(id);
            return;
        }
    }
    else 
    {
        if(Util::checkCircleCollision(position,
                    colliderRadius,
                    m_game->player->position,
                    m_game->player->colliderRadius))
        {
            m_game->PlayerDeath();
            m_game->shotsManager->DestroyShot(id);
            return;
        }
    }

    m_timePassed += deltaTime;
    if(m_timePassed >= m_lifeTime)
    {
        m_game->shotsManager->DestroyShot(id);
    }
}

void Shot::Render(Renderer* renderer)
{
    renderer->RenderCircle(position, 1, glm::vec3(1), 1);
}
