#include "ShotsManager.hpp"

ShotsManager::ShotsManager(Game* game) : m_game(game) {}


ShotsManager::~ShotsManager()
{
    for(auto i : m_shots)
        delete i.second;
    m_shots.clear();
}

void ShotsManager::Init()
{

}

void ShotsManager::SpawnShot(ShotType type, glm::vec2 position, glm::vec2 direction)
{
    Shot* shot = new Shot(m_game);
    shot->type = type;
    shot->position = position;
    shot->forward = direction;
    shot->speed = 500;
    shot->colliderRadius = 10;
    m_shots.emplace(shot->id, shot);
}

void ShotsManager::DestroyShot(unsigned int id)
{
    auto it = m_shots.find(id);
    if(it != m_shots.end())
    {
        delete it->second;
        it->second = nullptr;
    }
}

void ShotsManager::UpdateShots(float deltaTime)
{
    for(auto it = m_shots.begin(); it != m_shots.end();)
    {
        if(it->second)
        {
            it->second->Update(deltaTime);
            ++it;
        }
        else
        {
            it = m_shots.erase(it);
        }
    }
}

void ShotsManager::RenderShots(Renderer* renderer)
{
    for(auto it = m_shots.begin(); it != m_shots.end();)
    {
        if(it->second)
        {
            it->second->Render(renderer);
            ++it;
        }
        else
        {
            it = m_shots.erase(it);
        }
    }
}