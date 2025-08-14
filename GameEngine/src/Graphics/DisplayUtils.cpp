//
//  DisplayUtils.cpp
//  GameEngine
//
//  Created by John Saba on 7/7/24.
//

#include "DisplayUtils.h"
#include "Game.h"

namespace DisplayUtils {

SDL_Point getCurrentDisplaySize()
{
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    return {DM.w, DM.h};
}

SDL_Point getDisplayScaleFactor()
{
    SDL_Point displaySize = getCurrentDisplaySize();
    int w = displaySize.x / Game::LOGICAL_WIDTH;
    int h = displaySize.y / Game::LOGICAL_HEIGHT;
    return {w, h};
}

}

