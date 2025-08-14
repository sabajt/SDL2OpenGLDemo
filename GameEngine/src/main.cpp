//
//  main.cpp
//  GameEngine
//
//  Created by John Saba on 6/22/24.
//

#include "Game.h"
#include "Constants.h"
#include <SDL2/SDL.h>

int main(int argc, char* args[])
{
    // TODO: why getting the same random numbers?
    srand((unsigned int)time(NULL));

    const Uint64 fixedDt = Constants::MS_PER_UPDATE;
    const Uint64 maxFrameTime = Uint64(0.25f * 1000.0f);
    
    Game game;
    
    if (!game.init())
    {
        printf("Failed to initialize game\n");
        return -1;
    }
    
    Uint64 t = 0;
    Uint64 currentTime = SDL_GetTicks64();
    Uint64 lagTime = 0;
    
    while (!game.quitGame)
    {
        Uint64 newTime = SDL_GetTicks64();
        Uint64 frameTime = newTime - currentTime;
        if (frameTime > maxFrameTime)
        {
            frameTime = maxFrameTime;
            printf("simulation slowdown\n");
        }
        currentTime = newTime;
        
        lagTime += frameTime;
    
        game.handleInput();
        
        while (lagTime >= fixedDt)
        {
            game.update(t);
            t += fixedDt;
            lagTime -= fixedDt;
        }
        
        double dt = double(lagTime) / double(fixedDt);
        game.render(dt);
    }
    
    game.close();
    
    return 0;
}
