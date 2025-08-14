//
//  GoToBubblesCommand.hpp
//  GameEngine
//
//  Created by John Saba on 2/22/25.
//

#ifndef GoToBubblesCommand_hpp
#define GoToBubblesCommand_hpp

#include "Command.h"

class Game;

class GoToBubblesCommand : public Command
{
public:
    void execute(Game& game);
};

#endif /* GoToBubblesCommand_hpp */
