//
//  SelectCommand.cpp
//  GameEngine
//
//  Created by John Saba on 2/14/25.
//

#include "SelectCommand.hpp"
#include "Game.h"

void SelectCommand::execute(Game& game, int x, int y)
{
    /* 
     If implementing scale up using framebuffer in OpenGL instead,
     will this still be needed?
     */
    
    int ww, wh;
    SDL_GetWindowSize(gWindow, &ww, &wh);
    
    float sx = float(game.LOGICAL_WIDTH) / float(ww);
    float sy = float(game.LOGICAL_HEIGHT) / float(wh);
    
    float lx = float(x) * sx;
    float ly = float(y) * sy;
    
    game.selectedPos = glm::vec2(lx, ly) + game.camera;
}

