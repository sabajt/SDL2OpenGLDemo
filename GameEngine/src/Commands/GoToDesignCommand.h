//
//  GoToDesignCommand.h
//  GameEngine
//
//  Created by John Saba on 12/8/24.
//


#ifndef SwitchModeCommand_h
#define SwitchModeCommand_h

#include "Command.h"

class Game;

class GoToDesignCommand : public Command
{
public:
    void execute(Game& game);
};

#endif /* SwitchModeCommand_h */
