//
//  GoToBubblesCommand.cpp
//  GameEngine
//
//  Created by John Saba on 2/22/25.
//

#include "GoToBubblesCommand.hpp"
#include "Game.h"

void GoToBubblesCommand::execute(Game& game)
{
    switch (game.gameState)
    {
        case GAME_STATE_DESIGN:
            game.gameState = GAME_STATE_T_BEGIN_DESIGN_BUBBLES;
            break;
            
        default:
            break;
    }
}

