#include "HudManager.hpp"
#include "ResourceManager/ResourceManager.hpp"

HudManager::HudManager()
{
    m_playerTex = ResourceManager::GetTexture2D("ship");
}

void HudManager::Render(Renderer *renderer, TextRenderer *textRenderer)
{
    textRenderer->RenderText("00", 50, 1, 1.5f);
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

void HudManager::TakeLife()
{
    m_lives--;
}

