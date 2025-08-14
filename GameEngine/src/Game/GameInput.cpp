//
//  GameInput.cpp
//  GameEngine
//
//  Created by John Saba on 7/21/24.
//

#include "Game.h"
#include "InputUtils.h"
#include "CreateOrLoadBubbleCommand.hpp"
#include "QuitCommand.h"
#include "SelectCommand.hpp"
#include "GoToDesignCommand.h"
#include "GoToBubblesCommand.hpp"
#include "ShakeCommand.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_mouse.h>
#include <string>

void Game::setupInput()
{        
    /*
     
     Map default controlls
     
     */
    
    // Create or load bubble
    
    inputCommands[
        InputUtils::inputCommandKeyForKeycodeDown(SDLK_a)
    ] = new CreateOrLoadBubbleCommand("a");
    
    inputCommands[
        InputUtils::inputCommandKeyForKeycodeDown(SDLK_b)
    ] = new CreateOrLoadBubbleCommand("b");
    
    inputCommands[
        InputUtils::inputCommandKeyForKeycodeDown(SDLK_c)
    ] = new CreateOrLoadBubbleCommand("c");
    
    inputCommands[
        InputUtils::inputCommandKeyForKeycodeDown(SDLK_d)
    ] = new CreateOrLoadBubbleCommand("d");
    
    inputCommands[
        InputUtils::inputCommandKeyForKeycodeDown(SDLK_e)
    ] = new CreateOrLoadBubbleCommand("e");
    
    inputCommands[
        InputUtils::inputCommandKeyForKeycodeDown(SDLK_f)
    ] = new CreateOrLoadBubbleCommand("f");
    
    inputCommands[
        InputUtils::inputCommandKeyForKeycodeDown(SDLK_g)
    ] = new CreateOrLoadBubbleCommand("g");
    
    inputCommands[
        InputUtils::inputCommandKeyForKeycodeDown(SDLK_h)
    ] = new CreateOrLoadBubbleCommand("h");
    
    inputCommands[
        InputUtils::inputCommandKeyForKeycodeDown(SDLK_i)
    ] = new CreateOrLoadBubbleCommand("i");
    
    inputCommands[
        InputUtils::inputCommandKeyForKeycodeDown(SDLK_j)
    ] = new CreateOrLoadBubbleCommand("j");
    
    inputCommands[
        InputUtils::inputCommandKeyForKeycodeDown(SDLK_k)
    ] = new CreateOrLoadBubbleCommand("k");
    
    inputCommands[
        InputUtils::inputCommandKeyForKeycodeDown(SDLK_l)
    ] = new CreateOrLoadBubbleCommand("l");
    
    inputCommands[
        InputUtils::inputCommandKeyForKeycodeDown(SDLK_m)
    ] = new CreateOrLoadBubbleCommand("m");
    
    inputCommands[
        InputUtils::inputCommandKeyForKeycodeDown(SDLK_n)
    ] = new CreateOrLoadBubbleCommand("n");
    
    inputCommands[
        InputUtils::inputCommandKeyForKeycodeDown(SDLK_o)
    ] = new CreateOrLoadBubbleCommand("o");
    
    inputCommands[
        InputUtils::inputCommandKeyForKeycodeDown(SDLK_p)
    ] = new CreateOrLoadBubbleCommand("p");
    
    inputCommands[
        InputUtils::inputCommandKeyForKeycodeDown(SDLK_q)
    ] = new CreateOrLoadBubbleCommand("q");
    
    inputCommands[
        InputUtils::inputCommandKeyForKeycodeDown(SDLK_r)
    ] = new CreateOrLoadBubbleCommand("r");
    
    inputCommands[
        InputUtils::inputCommandKeyForKeycodeDown(SDLK_s)
    ] = new CreateOrLoadBubbleCommand("s");
    
    inputCommands[
        InputUtils::inputCommandKeyForKeycodeDown(SDLK_t)
    ] = new CreateOrLoadBubbleCommand("t");
    
    inputCommands[
        InputUtils::inputCommandKeyForKeycodeDown(SDLK_u)
    ] = new CreateOrLoadBubbleCommand("u");
    
    inputCommands[
        InputUtils::inputCommandKeyForKeycodeDown(SDLK_v)
    ] = new CreateOrLoadBubbleCommand("v");
    
    inputCommands[
        InputUtils::inputCommandKeyForKeycodeDown(SDLK_w)
    ] = new CreateOrLoadBubbleCommand("w");
    
    inputCommands[
        InputUtils::inputCommandKeyForKeycodeDown(SDLK_x)
    ] = new CreateOrLoadBubbleCommand("x");
    
    inputCommands[
        InputUtils::inputCommandKeyForKeycodeDown(SDLK_y)
    ] = new CreateOrLoadBubbleCommand("y");
    
    inputCommands[
        InputUtils::inputCommandKeyForKeycodeDown(SDLK_z)
    ] = new CreateOrLoadBubbleCommand("z");
    
    // Quit game
    
    inputCommands[
        InputUtils::inputCommandKeyForKeycodeDown(SDLK_ESCAPE)
    ] = new QuitCommand();
    
    // Select
    
    inputCommands[
        InputUtils::inputCommandKeyForMouseClickDown()
    ] = new SelectCommand();
    
    // Change screens
    
    inputCommands[
        InputUtils::inputCommandKeyForKeycodeDown(SDLK_RIGHT)
    ] = new GoToDesignCommand();
    
    inputCommands[
        InputUtils::inputCommandKeyForKeycodeDown(SDLK_LEFT)
    ] = new GoToBubblesCommand();
    
    // Shake
    
    inputCommands[
        InputUtils::inputCommandKeyForKeycodeDown(SDLK_SPACE)
    ] = new ShakeCommand();
    
}

void Game::teardownInput()
{
    for (const auto& [k, v] : inputCommands)
    {
        delete v;
    }
}

void Game::handleInput()
{
    SDL_Event event;
    SDL_JoystickID jID;
    
    // TODO: Is it bad to try / catch as a way to check for nil in map?
    // Should be easy to keep track of supported input another way
    while (SDL_PollEvent(&event) != 0)
    {
        switch (event.type)
        {
            case SDL_QUIT: 
            {
                quitGame = true;
                break;
            }
            case SDL_KEYDOWN: 
            {
                std::string inputKey =  InputUtils::inputCommandKeyForKeycodeDown(event.key.keysym.sym);
               
                try
                {
                    Command *command = inputCommands.at(inputKey);
                    command->execute(*this);
                } 
                catch (...)
                {
//                    printf("SDL_KEYDOWN not handled\n");
                }
                break;
            }
            case SDL_KEYUP:
            {
                std::string inputKey = InputUtils::inputCommandKeyForKeycodeUp(event.key.keysym.sym);
                try
                {
                    Command *command = inputCommands.at(inputKey);
                    command->execute(*this);
                }
                catch (...)
                {
//                    printf("SDL_KEYUP not handled\n");
                }
                break;
            }

            case SDL_CONTROLLERDEVICEADDED: 
            {
                // don't care just overwrite the only one for now
                controller1 = SDL_GameControllerOpen(event.cdevice.which);
                break;
            }
                
            case SDL_CONTROLLERDEVICEREMOVED: 
            {
                jID = SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(controller1));
                if (controller1 && event.cdevice.which == jID)
                {
                    SDL_GameControllerClose(controller1);
                    controller1 = InputUtils::findFirstController();
                }
                break;
            }
                
            case SDL_CONTROLLERBUTTONDOWN: 
            {
                jID = SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(controller1));
                
                // TODO: consider using event.cdevice.which instead
                if (controller1 && event.cdevice.which == jID)
                {
                    std::string inputKey = InputUtils::inputCommandKeyForButtonDown(event.cbutton.button);
                    try
                    {
                        Command *command = inputCommands.at(inputKey);
                        command->execute(*this);
                    } 
                    catch (...) 
                    {
//                        printf("SDL_CONTROLLERBUTTONDOWN not handled\n");
                    }
                }
                break;
            }
                
            case SDL_CONTROLLERBUTTONUP:
            {
                jID = SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(controller1));
                
                // TODO: consider using event.cdevice.which instead
                if (controller1 && event.cdevice.which == jID)
                {
                    std::string inputKey = InputUtils::inputCommandKeyForButtonUp(event.cbutton.button);
                    try
                    {
                        Command *command = inputCommands.at(inputKey);
                        command->execute(*this);
                    }
                    catch (...)
                    {
//                        printf("SDL_CONTROLLERBUTTONUP not handled\n");
                    }
                }
                break;
            }
                
            case SDL_MOUSEMOTION:
            {
                const int x = event.motion.xrel;
                const int y = event.motion.yrel;
                
                std::string inputKey = InputUtils::inputCommandKeyForMouseMoved();
                try
                {
                    Command *command = inputCommands.at(inputKey);
                    command->execute(*this, (float)x, (float)y);
                }
                catch (...)
                {
//                    printf("SDL_MOUSEMOTION not handled\n");
                }
                
                break;
            }
                
            case SDL_MOUSEWHEEL:
            {
                const int scroll = event.wheel.y;
                std::string inputKey = InputUtils::inputCommandKeyForMouseScrolled();
                
                try
                {
                    Command *command = inputCommands.at(inputKey);
                    command->execute(*this, scroll);
                }
                catch (...)
                {
//                    printf("SDL_MOUSEWHEEL not handled\n");
                }
                
                break;
            }
                
            case SDL_MOUSEBUTTONDOWN:
            {
                const int x = event.button.x;
                const int y = event.button.y;
                
                std::string inputKey = InputUtils::inputCommandKeyForMouseClickDown();
                try
                {
                    Command *command = inputCommands.at(inputKey);
                    command->execute(*this, x, y);
                }
                catch (...)
                {
//                    printf("SDL_MOUSEMOTION not handled\n");
                }
                
                break;
            }
                
            default:
                break;
                
        }
    }
}
