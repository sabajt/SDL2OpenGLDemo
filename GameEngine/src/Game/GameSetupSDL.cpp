//
//  GameSDL.cpp
//  GameEngine
//
//  Created by John Saba on 8/22/24.
//

#include <SDL2_Image/SDL_image.h>
#include "Game.h"

bool Game::initContextSDL()
{
    //Initialization flag
    bool success = true;
    
    //Set texture filtering to nearest (no anti-aliasing)
    if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0"))
    {
        printf("Warning: Linear texture filtering not enabled!");
    }
    
    // Create window, taking into account render scaling
    const SDL_Point defaultWindowSize = {SCREEN_WIDTH * 3, SCREEN_HEIGHT * 3};
    gWindow = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, defaultWindowSize.x, defaultWindowSize.y, SDL_WINDOW_SHOWN);
    if (gWindow == NULL)
    {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    //Create renderer for window
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if(gRenderer == NULL)
    {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }
    
    // Initialize renderer color
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    
    // Scale rendering
    SDL_RenderSetLogicalSize(gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    
    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        success = false;
    }
    
    //Initialize SDL_ttf
    if(TTF_Init() == -1)
    {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        return false;
    }
    
    return true;
}

bool Game::loadMediaSDL()
{
    bool success = true;
    
    // Load font
    gFont = TTF_OpenFont("OpenSans-Regular.ttf", 12);
    if(gFont == NULL)
    {
        printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    
    // TODO: load all images, and include color key info
//    for (auto i: imageMap)
//    {
//        images[i.first] = loadTexture(i.second);
//        if(images[i.first] == NULL)
//        {
//            printf("Failed to load %s\n", i.second.c_str());
//            success = false;
//        }
//    }
    
    // TODO: when to deallocate? use smart pointer?
    Texture *catHead = new Texture;
    std::string a = imageMap[IMAGE_CAT_HEAD];
    catHead->loadFromFile(a);

    images[IMAGE_CAT_HEAD] = catHead;

    Texture *catHeadColorKeyed = new Texture;
    std::string b = imageMap[IMAGE_CAT_HEAD_COLOR_KEYED];
    catHeadColorKeyed->loadFromFile(b, SDL_Color{0, 0xFF, 0, 0xFF});

    images[IMAGE_CAT_HEAD_COLOR_KEYED] = catHeadColorKeyed;
    
    return success;
}

void Game::setupSceneSDL()
{
    // TODO: separate (or remove) when rendering w/ openGL
    std::string textureFileName = imageMap[IMAGE_CAT_HEAD_COLOR_KEYED];

    // TODO: what is this std::move nonsense?
    auto entity1 = TextureEntity::createFromFile(textureFileName, Vec2(100, 50), Vec2(6,-3));
    entities.push_back(std::move(entity1));
    
    auto entity2 = TextureEntity::createFromFile(textureFileName, Vec2(0, 0), Vec2(18,2));
    entities.push_back(std::move(entity2));
    
    auto titleText = TextureEntity::createFromText("The quick brown fox jumps", SDL_Color{0, 0, 0}, Vec2(6, 6));
    entities.push_back(std::move(titleText));

}

void Game::closeSDL()
{
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;
}

