//
//  QuitCommand.h
//  GameEngine
//
//  Created by John Saba on 12/28/24.
//

#ifndef QuitCommand_h
#define QuitCommand_h

#include "Command.h"

class Game;

class QuitCommand : public Command
{
public:
    void execute(Game& game);
};

#endif /* QuitCommand_h */
