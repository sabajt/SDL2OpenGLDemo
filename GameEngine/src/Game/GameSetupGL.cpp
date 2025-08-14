//
//  GameGL.cpp
//  GameEngine
//
//  Created by John Saba on 8/22/24.
//

#include <glad/glad.h>
#include <SDL2/SDL_opengl.h>
#include <string>
#include "stb_image.h"
#include "Game.h"
#include "GLDebug.h"
#include "GLShader.h"
#include "ImageLoader.h"
#include "ResourceManager.h"
#include "WobbleObject.hpp"

bool Game::initContextGL()
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    // Create window
//    gWindow = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, LOGICAL_WIDTH, LOGICAL_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    gWindow = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, LOGICAL_WIDTH, LOGICAL_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);

    if (gWindow == NULL)
    {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }
    
    gOpenGLContext = SDL_GL_CreateContext(gWindow);
    
    int i = SDL_GetWindowDisplayIndex(gWindow);
    SDL_Rect j;
    SDL_GetDisplayBounds(i, &j);
    int dbw = j.w;
    int dbh = j.h;
    printf("\ndisplay bounds %i, %i\n", dbw, dbh);
    
    // Load OpenGL functions
    if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
    {
        printf("Failed to load OpenGL functions with Glad");
        return false;
    }
    printf("Vendor:   %s\n", glGetString(GL_VENDOR));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("Version:  %s\n", glGetString(GL_VERSION));
        
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    
    glm::mat4 projection = glm::ortho(0.0f, float(LOGICAL_WIDTH), float(LOGICAL_HEIGHT), 0.0f, -1.0f, 1.0f);

    // base shader
    std::string vsPath = SDL_GetBasePath();
    std::string vsName = "shader_base.vs";
    std::string vsFullPath = vsPath + vsName;
    std::string fsPath = (std::string)SDL_GetBasePath() + "shader_base.fs";
    
    GLShader shaderBase = ResourceManager::LoadShader(vsFullPath.c_str(), fsPath.c_str(), nullptr, "base");
    shaderBase.use();
    shaderBase.setMat4("projection", projection);
    shaderBase.setFloat("screenHeight", LOGICAL_HEIGHT);
    
//    // sprite shader
//    vsPath = SDL_GetBasePath();
//    vsName = "shader_2D.vs";
//    vsFullPath = vsPath + vsName;
//    fsPath = (std::string)SDL_GetBasePath() + "shader_2D.fs";
//    
//    GLShader shaderSprite = ResourceManager::LoadShader(vsFullPath.c_str(), fsPath.c_str(), nullptr, "2D");
//    shaderSprite.use();
//    shaderSprite.setInt("image", 0);
//    shaderSprite.setMat4("projection", projection);
    
    // renderers
    wobbleRenderer = new WobbleRenderer(shaderBase);
    
    sliderRenderer = new SliderRenderer(shaderBase);
    sliderRenderer->initRenderData();
    
    radioButtonRenderer = new RadioButtonRenderer(shaderBase);
    radioButtonRenderer->initRenderData();
    
    buttonRenderer = new ButtonRenderer(shaderBase);
    buttonRenderer->initRenderData();
    
    lineSegmentRenderer = new LineSegmentRenderer(shaderBase);

//    spriteRenderer = new SpriteRenderer(shaderSprite);

    return true;
}

void Game::closeGL()
{
    // TODO: cleanup all the stuff...
}
