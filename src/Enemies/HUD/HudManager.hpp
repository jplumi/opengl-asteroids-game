#pragma once

#include "Render/Renderer.hpp"
#include "Render/TextRenderer.hpp"
#include "Render/Texture2D.hpp"

class HudManager
{
public:
    HudManager();

    void Render(Renderer *renderer, TextRenderer *textRenderer);

    void AddPoints(int amount);
    void TakeLife();

    void Reset();

private:
    unsigned int m_score = 0;
    int m_lives = 3;

    Texture2D *m_playerTex;
};

