#include "Shot.hpp"

#include "ShotsManager.hpp"
#include "Enemies/EnemiesManager.hpp"
#include "Enemies/Ufo.hpp"

void Shot::Update(float deltaTime)
{
    Entity::Update(deltaTime);

    position += forward * speed * deltaTime;

    Entity* enemy = m_game->enemiesManager->CheckCollision(this);
    if(enemy != nullptr)
    {
        m_game->enemiesManager->DestroyEnemy(enemy->id);
        m_game->shotsManager->DestroyShot(id);
        return;
    }

    if(m_game->ufo->CheckCollision(this))
    {
        m_game->ufo->Die();
        m_game->shotsManager->DestroyShot(id);
        return;
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
