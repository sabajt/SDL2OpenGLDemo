//
//  QuitCommand.cpp
//  GameEngine
//
//  Created by John Saba on 12/28/24.
//

#include <stdio.h>
#include "QuitCommand.h"
#include "Game.h"

void QuitCommand::execute(Game& game)
{
    game.quitGame = true;
}

