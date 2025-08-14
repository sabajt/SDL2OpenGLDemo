//
//  CreateOrLoadBubbleCommand.hpp
//  GameEngine
//
//  Created by John Saba on 2/10/25.
//

#ifndef CreateOrLoadBubbleCommand_hpp
#define CreateOrLoadBubbleCommand_hpp

#include "Command.h"
#include <string>

class Game;

class CreateOrLoadBubbleCommand : public Command
{
public:
    CreateOrLoadBubbleCommand(std::string key) : key(key) {}
    
    std::string key;
    
    void execute(Game& game);
};

#endif /* CreateOrLoadBubbleCommand_hpp */
