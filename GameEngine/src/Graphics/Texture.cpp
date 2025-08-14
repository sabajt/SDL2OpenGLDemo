//
//  Texture.cpp
//  GameEngine
//
//  Created by John Saba on 7/8/24.
//

#include "Texture.h"
#include "Game.h"
#include <SDL2_image/SDL_image.h>
#include <SDL2_TTF/SDL_TTF.h>

Texture::Texture()
{
    // Initialize
    sdlTexture = NULL;
    width = 0;
    height = 0;
}

Texture::~Texture()
{
    // Deallocate
    free();
}

bool Texture::loadFromFile(std::string path, SDL_Color colorKey)
{
    // Get rid of preexisting texture
    free();

    // The final texture
    SDL_Texture* newTexture = NULL;

    // TODO: Why do this and not IMG_LoadTexture_RW...?
    // Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        // Color key image
        if (colorKey.r != 0 || colorKey.b != 0 || colorKey.g != 0 || colorKey.a != 0) {
            SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, colorKey.r, colorKey.g, colorKey.b));
        }

        // Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        else
        {
            // Get image dimensions
            width = loadedSurface->w;
            height = loadedSurface->h;
        }

        // Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    // Return success
    sdlTexture = newTexture;
    return sdlTexture != NULL;
}

bool Texture::loadFromRenderedText(std::string text, SDL_Color color )
{
    //Get rid of preexisting texture
    free();

    //Render text surface
    SDL_Surface* surface = TTF_RenderText_Solid(gFont, text.c_str(), color);
    if(surface == NULL)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        sdlTexture = SDL_CreateTextureFromSurface(gRenderer, surface);
        if(sdlTexture == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            width = surface->w;
            height = surface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface(surface);
    }
    
    return sdlTexture != NULL;
}

void Texture::free()
{
    // Free texture if it exists
    if(sdlTexture != NULL )
    {
        SDL_DestroyTexture(sdlTexture);
        sdlTexture = NULL;
        width = 0;
        height = 0;
    }
}

void Texture::render( int x, int y )
{
    // Set rendering space and render to screen
    SDL_Rect renderQuad = {x, y, width, height};
    SDL_RenderCopy(gRenderer, sdlTexture, NULL, &renderQuad);
}

int Texture::getWidth()
{
    return width;
}

int Texture::getHeight()
{
    return height;
}

