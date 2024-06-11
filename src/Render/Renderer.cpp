#include "Renderer.hpp"

#include "ResourceManager/ResourceManager.hpp"
#include "Defs.h"

Renderer::~Renderer()
{
    glDeleteVertexArrays(1, &m_quadVAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
    delete m_texShader;
}

void Renderer::InitRenderData()
{
    float vertices[] = {
        // pos      // tex
        1.0f, 1.0f, 1.0f, 1.0f, // top right
        1.0f, 0.0f, 1.0f, 0.0f, // bottom right
        0.0f, 0.0f, 0.0f, 0.0f, // bottom left
        0.0f, 1.0f, 0.0f, 1.0f, // top left
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    glGenVertexArrays(1, &m_quadVAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_quadVAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) , vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    m_texShader = ResourceManager::LoadShader("texShader",
        "/Users/joaolumi/Documents/cpp/asteroids/resources/shaders/base.vert",
        "/Users/joaolumi/Documents/cpp/asteroids/resources/shaders/base.frag");

    glm::mat4 projection = glm::ortho(0.0f, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT, 0.0f, -1.0f, 1.0f);

    m_texShader->Use();
    m_texShader->SetInt("image", 0);
    m_texShader->SetMat4("projection", projection);

    m_circleShader = ResourceManager::LoadShader("circleShader",
        "/Users/joaolumi/Documents/cpp/asteroids/resources/shaders/circle.vert",
        "/Users/joaolumi/Documents/cpp/asteroids/resources/shaders/circle.frag");

    m_circleShader->Use();
    m_circleShader->SetMat4("projection", projection);
}

void Renderer::RenderTexture2D(Texture2D* texture, glm::vec2 position, 
        glm::vec2 size,
        float rotate, 
        glm::vec3 color) const
{
    m_texShader->Use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 1.0f));

    // rotate from the center of the sprite
    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

    model = glm::scale(model, glm::vec3(size, 1.0f));

    glActiveTexture(GL_TEXTURE0);
    texture->Bind();

    m_texShader->SetMat4("model", model);
    m_texShader->SetVec3("objectColor", color.x, color.y, color.z);

    glBindVertexArray(m_quadVAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Renderer::RenderCircle(glm::vec2 position, glm::vec2 size, glm::vec3 color, float thickness) const
{
    m_circleShader->Use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 1.0f));

    model = glm::scale(model, glm::vec3(size, 1.0f));

    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D, 0);

    m_circleShader->SetMat4("model", model);
    m_circleShader->SetVec3("objectColor", color.x, color.y, color.z);
    m_circleShader->SetFloat("thickness", thickness);

    glBindVertexArray(m_quadVAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
