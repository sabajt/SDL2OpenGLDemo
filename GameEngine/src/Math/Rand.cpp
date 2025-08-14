//
//  Rand.cpp
//  GameEngine
//
//  Created by John Saba on 2/22/25.
//

#include "Rand.hpp"
#include <stdlib.h>

float normRand()
{
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

float unitRand()
{
    return (normRand() * 2.0f) - 1.0f;
}

int intRandRange(int m, int n)
{
    return m + rand() / (RAND_MAX / (n - m + 1) + 1);
}
