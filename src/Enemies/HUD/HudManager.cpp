#include "HudManager.hpp"
#include "ResourceManager/ResourceManager.hpp"
#include <string>

HudManager::HudManager()
{
    m_playerTex = ResourceManager::GetTexture2D("ship");
}

void HudManager::Render(Renderer *renderer, TextRenderer *textRenderer)
{
    if(m_score == 0)
        textRenderer->RenderText("00", 50, 1, 1.5f);
    else
        textRenderer->RenderText(std::to_string(m_score), 50, 1, 1.5f);
    int xPos = 60;
    for(int i = 0; i < m_lives; i++)
    {
        renderer->RenderTexture2D(
                m_playerTex,
                glm::vec2(xPos, 60),
                glm::vec2(40),
                -90);
        xPos += 30;
    }
}

void HudManager::AddPoints(int amount)
{
    m_score += amount;
}

void HudManager::TakeLife()
{
    m_lives--;
}

