//
//  DisplayUtils.h
//  GameEngine
//
//  Created by John Saba on 7/7/24.
//

#ifndef DisplayUtils_h
#define DisplayUtils_h

#include <SDL2/SDL.h>

namespace DisplayUtils {

SDL_Point getCurrentDisplaySize();
SDL_Point getDisplayScaleFactor();

}

#endif /* DisplayUtils_h */
