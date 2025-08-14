//
//  ShakeCommand.cpp
//  GameEngine
//
//  Created by John Saba on 2/24/25.
//

#include "ShakeCommand.hpp"

#include "Game.h"

void ShakeCommand::execute(Game& game)
{
    game.shake = true;
}
