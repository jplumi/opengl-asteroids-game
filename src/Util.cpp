#include "Util.h"

namespace Util
{
    float lerp(float min, float max, float value)
    {
        return min + (max - min) * value;
    }

    bool checkBoxCollision(const glm::vec2 &aPos, const glm::vec2 &aSize, const glm::vec2 &bPos, const glm::vec2 &bSize)
    {
        if(aPos.x + aSize.x < bPos.x)
            return false;
        if(aPos.x > bPos.x + bSize.x)
            return false;
        if(aPos.y + aSize.y < bPos.y)
            return false;
        if(aPos.y > bPos.y + bSize.y)
            return false;
        
        return true;
    }

    bool checkCircleCollision(const glm::vec2 &aPos, float aRadius,
                            const glm::vec2 &bPos, float bRadius)
    {
        return glm::length(aPos - bPos) < bRadius + aRadius;
    }

    glm::vec2 randomDirection()
    {
        return glm::normalize(glm::vec2(rand() - RAND_MAX/2, rand() - RAND_MAX/2));
    }
}