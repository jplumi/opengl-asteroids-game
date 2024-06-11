#pragma once

#include "Shader.hpp"
#include "Texture2D.hpp"

class Renderer
{
public:
    ~Renderer();

    void InitRenderData();
    void RenderTexture2D(Texture2D* texture, glm::vec2 position, 
        glm::vec2 size = glm::vec2(50.0f, 50.0f), float rotate = 0.0f, 
        glm::vec3 color = glm::vec3(1.0f)) const;
    void RenderCircle(glm::vec2 position, glm::vec2 size, glm::vec3 color, float thickness) const;

private:
    Shader* m_texShader;
    Shader* m_circleShader;
    unsigned int m_quadVAO;
    unsigned int m_VBO;
    unsigned int m_EBO;
};