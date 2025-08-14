//
//  SelectCommand.hpp
//  GameEngine
//
//  Created by John Saba on 2/14/25.
//

#ifndef SelectCommand_hpp
#define SelectCommand_hpp

#include "Command.h"

class Game;

class SelectCommand : public Command
{
public:
    void execute(Game& game, int x, int y);
};

#endif /* SelectCommand_hpp */
