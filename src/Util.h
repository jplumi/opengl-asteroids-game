#pragma once

float lerp(float min, float max, float value)
{
    return min + (max - min) * value;
}