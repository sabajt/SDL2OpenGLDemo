//
//  Ease.cpp
//  GameEngine
//
//  Created by John Saba on 2/22/25.
//

#include "Ease.hpp"
#include <math.h>

float easeOutExpo(float t)
{
    return t == 1.0f ? 1.0f : 1.0f - pow(2.0f, -10.0f * t);
}
