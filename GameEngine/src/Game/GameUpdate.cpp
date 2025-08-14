//
//  GameUpdate.cpp
//  GameEngine
//
//  Created by John Saba on 7/21/24.
//

#include "Game.h"
#include "Constants.h"
#include <algorithm>
#include "Lerp.h"
#include "Ease.hpp"
#include "Rand.hpp"

void Game::update(Uint64 ticks)
{
    // Is this the right way to cast in this case?
    float t = static_cast<float>(ticks) / 1000.0f;
    
    // Handle last selected point
    if (selectedPos != GLM_VEC2_NONE)
    {     
        if (numSidesSlider->handleSelection(selectedPos))
        {
            designUpdate = true;
        }
        if (renderModeRadioButtons->handleSelection(selectedPos))
        {
            designUpdate = true;
        }
        if (redSlider->handleSelection(selectedPos))
        {
            designUpdate = true;
        }
        if (greenSlider->handleSelection(selectedPos))
        {
            designUpdate = true;
        }
        if (blueSlider->handleSelection(selectedPos))
        {
            designUpdate = true;
        }
        if (pullSlider->handleSelection(selectedPos))
        {
            designUpdate = true;
        }
        if (dampSlider->handleSelection(selectedPos))
        {
            designUpdate = true;
        }
        if (wobbleStartSpeedSlider->handleSelection(selectedPos))
        {
            designUpdate = true;
        }
        if (growStartSlider->handleSelection(selectedPos))
        {
            designUpdate = true;
        }
        if (growEndSlider->handleSelection(selectedPos))
        {
            designUpdate = true;
        }
        if (decaySlider->handleSelection(selectedPos))
        {
            designUpdate = true;
        }
        if (randomButton->handleSelection(selectedPos))
        {
            randomizeLoadout(currentLetterKey);
            designUpdate = true;
        }

        selectedPos = GLM_VEC2_NONE;
    }
    
    // Update user-instanced bubbles
    for (auto iter = bubs.begin(); iter != bubs.end();)
    {
        WobbleObject &bub = *iter;
        if (bub.shouldDelete)
        {
            wobbleRenderer->deleteData(bub);
            iter = bubs.erase(iter);
        }
        else
        {
            if (shake)
            {
                bub.shake();
            }
            bub.update();
            iter++;
        }
    }
    
    // Update loadout if letter key pressed
    if (currentLetterUpdate != NO_LETTER_UPDATE)
    {
        initLoadout(currentLetterUpdate);
        designUpdate = true;
    }
    
    // Loop design bubble if it expires
    if (designBubble->shouldDelete)
    {
        designUpdate = true;
    }
    
    // Replace design bubble if update flag
    if (designUpdate)
    {
        initDesignBubble();
    }
    
    // Update letter
    currentLetterObj->update();
    
    // Update design prototype bubble
    if (shake)
    {
        designBubble->shake();
    }
    designBubble->update();
    
    if (shake)
    {
        shake = false;
    }
    
    // Update arrows
    leftArrowObj->update();
    rightArrowObj->update();
    
    // Update random button
    randomButton->update();
    
    // Bubble screen: create new bubble
    if (createBubble != NO_BUBBLE_UPDATE)
    {
        WobbleData wd = {};
        wd.id = currentBubbleId;
        wd.fadeOut = true;
        
        float px = normRand() * static_cast<float>(LOGICAL_WIDTH);
        float py = normRand() * static_cast<float>(LOGICAL_HEIGHT);
        wd.pos = glm::vec2(px, py);
        
        float speed = 3.0f;
        wd.vel = glm::vec2(unitRand() * speed, unitRand() * speed);
        
        // Configurable loadout
        
        LoadoutData lod = loadout[createBubble];
        
        wd.renderMode = WobbleRenderMode(lod.renderModeRadioButtons->selectedButton);
        wd.res = lod.numSidesSlider->val;
        wd.radStart = lod.growStartSlider->normVal() * RAD_START_MAX;
        wd.radEnd = lod.growEndSlider->normVal() * RAD_END_MAX;
        wd.life = static_cast<int>(lod.decaySlider->normVal() * LIFE_MAX);
        wd.pull = lod.pullSlider->normVal() * PULL_MAX;
        wd.damp = lod.dampSlider->normVal() * DAMP_MAX;
        wd.wobbleStartSpeed = lod.wobbleStartSpeedSlider->normVal() * WOBBLE_START_SPEED_MAX;
        
        float r = lod.redSlider->normVal();
        float g = lod.greenSlider->normVal();
        float b = lod.blueSlider->normVal();
        wd.col = glm::vec3(r, g, b);
        
        WobbleObject bub = WobbleObject(wd);
        wobbleRenderer->initRenderData(bub);
        
        bubs.push_back(bub);
        currentBubbleId++;
        
        createBubble = NO_BUBBLE_UPDATE;
    }
    
    /*
     
     Update camera
     
     */
    switch (gameState)
    {
        case GAME_STATE_T_BEGIN_BUBBLES_DESIGN:
        {
            // Begin transition, fallthrough to next state
            transitionBeginT = t;
            gameState = GAME_STATE_T_BUBBLES_DESIGN;
        }
        case GAME_STATE_T_BUBBLES_DESIGN:
        {
            // Transition to design screen
            const glm::vec2 TPOS = glm::vec2(static_cast<float>(LOGICAL_WIDTH), 0.0f);
            const float DUR = 0.33f;
            
            float tt = t - transitionBeginT;
            float percent = tt / DUR;
            
            if (percent >= 1.0f)
            {
                camera = TPOS;
                lastCamera = camera;
                gameState = GAME_STATE_DESIGN;
                transitionBeginT = 0.0f;
            }
            else
            {
                lastCamera = camera;
                camera = lerp(glm::vec2(0.0f, 0.0f), TPOS, easeOutExpo(percent));
            }
            
            break;
        }
        case GAME_STATE_T_BEGIN_DESIGN_BUBBLES:
        {
            // Begin transition, fallthrough to next state
            transitionBeginT = t;
            gameState = GAME_STATE_T_DESIGN_BUBBLES;
        }
        case GAME_STATE_T_DESIGN_BUBBLES:
        {
            // Transition to design screen
            const glm::vec2 TPOS = glm::vec2(0.0f, 0.0f);
            const float DUR = 0.33f;
            
            float tt = t - transitionBeginT;
            float percent = tt / DUR;
            
            if (percent >= 1.0f)
            {
                camera =  TPOS;
                lastCamera = camera;
                gameState = GAME_STATE_BUBBLES;
                transitionBeginT = 0.0f;
            }
            else
            {
                lastCamera = camera;
                camera = lerp(glm::vec2(static_cast<float>(LOGICAL_WIDTH), 0.0f), TPOS, easeOutExpo(percent));
            }
            
            break;
        }
        default:
        {
            break;
        }
    }
}


