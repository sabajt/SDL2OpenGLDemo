//
//  Command.h
//  GameEngine
//
//  Created by John Saba on 12/8/24.
//

#ifndef Command_h
#define Command_h

class Game;

class Command
{
public:
    virtual ~Command() {}
    virtual void execute(Game& game) {}
    virtual void execute(Game& game, int x, int y) {}
    virtual void execute(Game& game, int offset) {}    
};

#endif /* Command_h */
