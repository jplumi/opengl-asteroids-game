#pragma once

#include <glm/glm.hpp>

namespace Util
{
    float lerp(float min, float max, float value);

    bool checkBoxCollision(const glm::vec2 &aPos, const glm::vec2 &aSize, const glm::vec2 &bPos, const glm::vec2 &bSize);

    bool checkCircleCollision(const glm::vec2 &aPos, float aRadius,
                            const glm::vec2 &bPos, float bRadius);

    glm::vec2 randomDirection();
}