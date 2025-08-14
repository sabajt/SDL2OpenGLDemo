//
//  ShakeCommand.hpp
//  GameEngine
//
//  Created by John Saba on 2/24/25.
//

#ifndef ShakeCommand_hpp
#define ShakeCommand_hpp

#include "Command.h"

class Game;

class ShakeCommand : public Command
{
public:
    void execute(Game& game);
};

#endif /* ShakeCommand_hpp */
