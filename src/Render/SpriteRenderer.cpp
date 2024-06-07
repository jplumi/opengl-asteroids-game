#include "SpriteRenderer.hpp"
#include "Defs.h"

SpriteRenderer::SpriteRenderer(Shader &shader)
{
    _shader = shader;
    InitRenderData();
}

SpriteRenderer::~SpriteRenderer()
{
    glDeleteVertexArrays(1, &_quadVAO);
    glDeleteBuffers(1, &_EBO);
}

void SpriteRenderer::InitRenderData()
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

    unsigned int VBO;
    glGenVertexArrays(1, &_quadVAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &_EBO);

    glBindVertexArray(_quadVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) , vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void SpriteRenderer::DrawSprite(const Texture2D &texture, glm::vec2 position, 
        glm::vec2 size,
        float rotate, 
        glm::vec3 color) const
{
    glBindVertexArray(_quadVAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 1.0f));

    // rotate from the center of the sprite
    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

    model = glm::scale(model, glm::vec3(size, 1.0f));

    _shader.Use();

    _shader.SetMat4("model", model);
    _shader.SetVec3("objectColor", color.x, color.y, color.z);

    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}