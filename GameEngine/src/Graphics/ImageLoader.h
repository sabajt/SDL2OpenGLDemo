//
//  ImageLoader.h
//  GameEngine
//
//  Created by John Saba on 9/18/24.
//

#ifndef ImageLoader_h
#define ImageLoader_h

#include <assert.h>
#include <string>
#include "stb_image.h"

struct Image
{
    Image(std::string name)
    {
        std::string fullPath = (std::string)SDL_GetBasePath() + name;

        int x, y, n;
        data = stbi_load(fullPath.c_str(), &x, &y, &n, 0);
        if (data == NULL)
        {
            printf("Failed to load image with STB\n");
            assert(false);
        }
        else
        {
            this->x = x;
            this->y = y;
            
            printf("Loaded image with STB, x = %i, y = %i, n = %i\n", x, y, n);
        }
    }
    
    unsigned char *data;
    int x, y;
};

#endif /* ImageLoader_h */
