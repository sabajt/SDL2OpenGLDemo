//
//  InputUtils.h
//  GameEngine
//
//  Created by John Saba on 12/1/24.
//

#ifndef InputUtils_h
#define InputUtils_h

#include <SDL2/SDL.h>

namespace InputUtils
{

// Find controller

inline SDL_GameController *findFirstController()
{
    for (int i = 0; i < SDL_NumJoysticks(); i++)
    {
        if (SDL_IsGameController(i))
        {
            return SDL_GameControllerOpen(i);
        }
    }
    return nullptr;
}

// Keyboard command keys

inline std::string inputCommandKeyForKeycodeDown(SDL_Keycode keycode)
{
    return "KEY_DOWN_" + std::to_string(keycode);
}

inline std::string inputCommandKeyForKeycodeUp(SDL_Keycode keycode)
{
    return "KEY_UP_" + std::to_string(keycode);
}

// Controller command keys

/// @param button SDL_GameControllerButton
inline std::string inputCommandKeyForButtonDown(Uint8 button)
{ // See SDL_GameControllerButton for values
    return "BUTTON_DOWN_" + std::to_string(button);
}

/// @param button SDL_GameControllerButton
inline std::string inputCommandKeyForButtonUp(Uint8 button)
{ // See SDL_GameControllerButton for values
    return "BUTTON_UP_" + std::to_string(button);
}

// Mouse command keys

inline std::string inputCommandKeyForMouseMoved()
{
    return "MOUSE_MOVED";
}

inline std::string inputCommandKeyForMouseScrolled()
{
    return "MOUSE_SCROLLED";
}

inline std::string inputCommandKeyForMouseClickDown()
{
    return "MOUSE_CLICK_DOWN";
}

}

#endif /* InputUtils_h */


