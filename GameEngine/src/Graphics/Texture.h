//
//  Texture.h
//  GameEngine
//
//  Created by John Saba on 7/7/24.
//

#ifndef Texture_h
#define Texture_h

#include <string>
#include <SDL2/SDL.h>

// Texture wrapper class
class Texture
{
    public:
        // Initializes variables
        Texture();

        // Deallocates memory
        ~Texture();

        // Loads image at specified path
        bool loadFromFile(std::string path, SDL_Color colorKey = {0,0,0,0});

        // Creates image from font string
        bool loadFromRenderedText(std::string textureText, SDL_Color textColor);

        // Deallocates texture
        void free();

        // Renders texture at given point
        void render(int x, int y);

        // Gets image dimensions
        int getWidth();
        int getHeight();

    private:
        // The actual hardware texture
        SDL_Texture* sdlTexture;

        //Image dimensions
        int width;
        int height;
};

#endif /* Texture_h */
