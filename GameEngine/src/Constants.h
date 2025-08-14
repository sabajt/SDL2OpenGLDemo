//
//  Constants.h
//  GameEngine
//
//  Created by John Saba on 8/4/24.
//

#ifndef Constants_h
#define Constants_h

#include "SDL2/SDL.h"
#include <vector>
#include <string>

namespace Constants {

const Uint64 MS_PER_UPDATE = 16;
const double DT_FIXED = double(MS_PER_UPDATE) / 1000.0;

}

enum RenderType
{
    RT_PASSTHRU = 0,
    RT_CIRCLE,
    RT_GRAD,
    RT_COOL
};

// UI wobble config
static constexpr float UI_WOBBLE_PULL = 0.5f;
static constexpr float UI_WOBBLE_DAMP = 0.02f;
static constexpr float UI_WOBBLE_START_SPEED = 1.0f;

// Bubble loadout keys
const std::vector<std::string> LOADOUT_KEYS = 
{
    "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"
};

#endif /* Constants_h */
