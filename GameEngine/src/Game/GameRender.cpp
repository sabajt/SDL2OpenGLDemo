//
//  GameRender.cpp
//  GameEngine
//
//  Created by John Saba on 7/21/24.
//

#include <glad/glad.h>
#include "Game.h"
#include "Lerp.h"
#include "ResourceManager.h"

void Game::render(double dt)
{
    // TODO: double dt is silently cast to float everywhere - figure out if problem / how to handle
    
    // Clear the screen to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    // testing just drawing a sprite
//    auto texture = ResourceManager::GetTexture("smallcat");
//    spriteRenderer->DrawSprite(texture, // texture
//                               glm::vec2(float(SCREEN_WIDTH) / 2.0f, float(SCREEN_HEIGHT) / 2.0f), // pos
//                               glm::vec2(25.0f, 25.0f), // size
//                               0.0f, // rotation
//                               glm::vec3(0.0f, 1.0f, 0.0f)); // color
    
    // drawing levels with sprite renderer
//    this->Levels[this->Level].Draw(*renderer);
//    Player->Draw(*renderer);
    
    // User instantiated bubbles
    for (auto &bub: bubs)
    {
        wobbleRenderer->render(*this, dt, bub);
    }
    
    // Bubble screen
    if (gameState != GAME_STATE_DESIGN)
    {
        // Right arrow
        wobbleRenderer->render(*this, dt, *rightArrowObj);
    }
    
    if (gameState != GAME_STATE_BUBBLES)
    {
        // Design prototype bubble
        wobbleRenderer->render(*this, dt, *designBubble);
        
        // Current loaded letter
        wobbleRenderer->render(*this, dt, *currentLetterObj);
        
        // Left arrow
        wobbleRenderer->render(*this, dt, *leftArrowObj);

        // Controls
        sliderRenderer->render(*this, dt, *numSidesSlider);
        radioButtonRenderer->render(*this, dt, *renderModeRadioButtons);
        sliderRenderer->render(*this, dt, *redSlider);
        sliderRenderer->render(*this, dt, *greenSlider);
        sliderRenderer->render(*this, dt, *blueSlider);
        sliderRenderer->render(*this, dt, *pullSlider);
        sliderRenderer->render(*this, dt, *dampSlider);
        sliderRenderer->render(*this, dt, *wobbleStartSpeedSlider);
        sliderRenderer->render(*this, dt, *growStartSlider);
        sliderRenderer->render(*this, dt, *growEndSlider);
        sliderRenderer->render(*this, dt, *decaySlider);
        buttonRenderer->render(*this, dt, *randomButton);
        
        for (LineSegmentObject &textObj: controlsTextAndLines)
        {
            lineSegmentRenderer->render(*this, dt, textObj);
        }
    }
    
    // SDL doc says to do this on macOS before swap,
    // but that it's the default if not using glBindFramebuffer??
//    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0)
    SDL_GL_SwapWindow(gWindow);
}

