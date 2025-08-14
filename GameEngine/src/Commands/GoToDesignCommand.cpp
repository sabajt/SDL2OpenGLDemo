//
//  Actions.cpp
//  GameEngine
//
//  Created by John Saba on 12/8/24.
//

#include "GoToDesignCommand.h"
#include "Game.h"

void GoToDesignCommand::execute(Game& game) 
{
    switch (game.gameState)
    {
        case GAME_STATE_BUBBLES:
            game.gameState = GAME_STATE_T_BEGIN_BUBBLES_DESIGN;
            break;
            
        default:
            break;
    }
}

