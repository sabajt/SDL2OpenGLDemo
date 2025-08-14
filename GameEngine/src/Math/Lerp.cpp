//
//  Lerp.cpp
//  GameEngine
//
//  Created by John Saba on 2/11/25.
//

#include "Lerp.h"

float lerp(float a, float b, float t)
{
    return a * (1.0f - t) + b * t;
}

glm::vec3 lerp(glm::vec3 a, glm::vec3 b, float t)
{
    return a * (1.0f - t) + b * t;
}

glm::vec2 lerp(glm::vec2 a, glm::vec2 b, float t)
{
    return a * (1.0f - t) + b * t;
}

