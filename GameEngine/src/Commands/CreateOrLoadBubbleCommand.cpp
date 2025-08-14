//
//  CreateOrLoadBubbleCommand.cpp
//  GameEngine
//
//  Created by John Saba on 2/10/25.
//

#include "CreateOrLoadBubbleCommand.hpp"
#include "Game.h"

void CreateOrLoadBubbleCommand::execute(Game& game)
{
    switch (game.gameState)
    {
        case GAME_STATE_DESIGN:
            if (game.currentLetterKey != key)
            {
                game.currentLetterUpdate = key;
            }
            break;
            
        case GAME_STATE_BUBBLES:
            game.createBubble = key;
            break;
            
        default:
            break;
    }
}
