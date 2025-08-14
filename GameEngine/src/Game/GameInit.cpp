//
//  Game.cpp
//  GameEngine
//
//  Created by John Saba on 6/23/24.
//

#include "Game.h"
#include "InputUtils.h"
#include "ResourceManager.h"
#include "VertexGeo.hpp"
#include "ButtonObject.hpp"

bool Game::init()
{
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) < 0)
    {
        printf("Failed to initialize SDL. Error: %s\n", SDL_GetError());
        return false;
    }
    
    if (!initContextGL())
    {
        printf("Failed to intialize OpenGL\n");
        return false;
    }
    
    // Load textures
    ResourceManager::LoadTexture("smallcat.png", true, "smallcat");
    
    // Initialize input system
    setupInput();
    
    // Initialize game objects
    initObjects();
    
    // Randomize every bubble loadout
    randomizeAllLoadouts();
    
    return true;
}

void Game::initObjects()
{
    float screenWidth = static_cast<float>(LOGICAL_WIDTH);
    float screenHeight = static_cast<float>(LOGICAL_HEIGHT);

    // Build loadout control map
    for (auto k: LOADOUT_KEYS)
    {
        SliderData numSidesData = {};
        numSidesData.pos = glm::vec2(CONTROL_PANEL_LEFT, CONTROL_PANEL_TOP_LINE + CONTROL_PADDING);
        numSidesData.size = glm::vec2(CONTROL_PANEL_WIDTH, SLIDER_HEIGHT);
        numSidesData.minVal = 3;
        numSidesData.maxVal = 100;
        numSidesData.initVal = 40;
        SliderObject *numSidesSliderObj = new SliderObject(numSidesData);
        
        RadioButtonData renderModeData = {};
        renderModeData.pos = glm::vec2(CONTROL_PANEL_LEFT, numSidesSliderObj->pos.y + SLIDER_HEIGHT + CONTROL_PADDING);
        renderModeData.col = glm::vec3(1.0f, 1.0f, 1.0f);
        renderModeData.buttonSize = glm::vec2(SLIDER_HEIGHT, SLIDER_HEIGHT);
        renderModeData.numButtons = 5;
        RadioButtonObject *renderModeRadioButtonsObj = new RadioButtonObject(renderModeData);
        
        SliderData redSliderData = {};
        redSliderData.pos = glm::vec2(CONTROL_PANEL_LEFT, renderModeRadioButtonsObj->pos.y + SLIDER_HEIGHT + CONTROL_PADDING);
        redSliderData.size = glm::vec2(CONTROL_PANEL_WIDTH, SLIDER_HEIGHT);
        redSliderData.col = glm::vec3(1.0f, 0.0f, 0.0f);
        redSliderData.minVal = 0;
        redSliderData.maxVal = 255;
        redSliderData.initVal = 255;
        SliderObject *redSliderObj = new SliderObject(redSliderData);
        
        SliderData greenSliderData = {};
        greenSliderData.pos = glm::vec2(CONTROL_PANEL_LEFT, redSliderObj->pos.y + SLIDER_HEIGHT + CONTROL_PADDING);
        greenSliderData.size = glm::vec2(CONTROL_PANEL_WIDTH, SLIDER_HEIGHT);
        greenSliderData.col = glm::vec3(0.0f, 1.0f, 0.0f);
        greenSliderData.minVal = 0;
        greenSliderData.maxVal = 255;
        greenSliderData.initVal = 255;
        SliderObject *greenSliderObj = new SliderObject(greenSliderData);
        
        SliderData blueSliderData = {};
        blueSliderData.pos = glm::vec2(CONTROL_PANEL_LEFT, greenSliderObj->pos.y + SLIDER_HEIGHT + CONTROL_PADDING);
        blueSliderData.size = glm::vec2(CONTROL_PANEL_WIDTH, SLIDER_HEIGHT);
        blueSliderData.col = glm::vec3(0.0f, 0.0f, 1.0f);
        blueSliderData.minVal = 0;
        blueSliderData.maxVal = 255;
        blueSliderData.initVal = 255;
        SliderObject *blueSliderObj = new SliderObject(blueSliderData);
        
        SliderData pullSliderData = {};
        pullSliderData.pos = glm::vec2(CONTROL_PANEL_LEFT, blueSliderObj->pos.y + SLIDER_HEIGHT + CONTROL_PADDING);
        pullSliderData.size = glm::vec2(CONTROL_PANEL_WIDTH, SLIDER_HEIGHT);
        pullSliderData.minVal = 0;
        pullSliderData.maxVal = 300;
        pullSliderData.initVal = 20;
        SliderObject *pullSliderObj = new SliderObject(pullSliderData);
        
        SliderData dampSliderData = {};
        dampSliderData.pos = glm::vec2(CONTROL_PANEL_LEFT, pullSliderObj->pos.y + SLIDER_HEIGHT + CONTROL_PADDING);
        dampSliderData.size = glm::vec2(CONTROL_PANEL_WIDTH, SLIDER_HEIGHT);
        dampSliderData.minVal = 0;
        dampSliderData.maxVal = 500;
        dampSliderData.initVal = 5;
        SliderObject *dampSliderObj = new SliderObject(dampSliderData);
        
        SliderData wobbleStartSpeedSliderData = {};
        wobbleStartSpeedSliderData.pos = glm::vec2(CONTROL_PANEL_LEFT, dampSliderObj->pos.y + SLIDER_HEIGHT + CONTROL_PADDING);
        wobbleStartSpeedSliderData.size = glm::vec2(CONTROL_PANEL_WIDTH, SLIDER_HEIGHT);
        wobbleStartSpeedSliderData.minVal = 0;
        wobbleStartSpeedSliderData.maxVal = 100;
        wobbleStartSpeedSliderData.initVal = 10;
        SliderObject *wobbleStartSpeedSliderObj = new SliderObject(wobbleStartSpeedSliderData);
        
        SliderData growStartSliderData = {};
        growStartSliderData.pos = glm::vec2(CONTROL_PANEL_LEFT, wobbleStartSpeedSliderObj->pos.y + SLIDER_HEIGHT + CONTROL_PADDING);
        growStartSliderData.size = glm::vec2(CONTROL_PANEL_WIDTH, SLIDER_HEIGHT);
        growStartSliderData.minVal = 1;
        growStartSliderData.maxVal = 100;
        growStartSliderData.initVal = 5;
        SliderObject *growStartSliderObj = new SliderObject(growStartSliderData);
        
        SliderData growEndSliderData = {};
        growEndSliderData.pos = glm::vec2(CONTROL_PANEL_LEFT, growStartSliderObj->pos.y + SLIDER_HEIGHT + CONTROL_PADDING);
        growEndSliderData.size = glm::vec2(CONTROL_PANEL_WIDTH, SLIDER_HEIGHT);
        growEndSliderData.minVal = 1;
        growEndSliderData.maxVal = 100;
        growEndSliderData.initVal = 40;
        SliderObject *growEndSliderObj = new SliderObject(growEndSliderData);
        
        SliderData decaySliderData = {};
        decaySliderData.pos = glm::vec2(CONTROL_PANEL_LEFT, growEndSliderObj->pos.y + SLIDER_HEIGHT + CONTROL_PADDING);
        decaySliderData.size = glm::vec2(CONTROL_PANEL_WIDTH, SLIDER_HEIGHT);
        decaySliderData.minVal = 8;
        decaySliderData.maxVal = 40;
        decaySliderData.initVal = 20;
        SliderObject *decaySliderObj = new SliderObject(decaySliderData);
        
        LoadoutData lod = LoadoutData();
        lod.numSidesSlider = numSidesSliderObj;
        lod.renderModeRadioButtons = renderModeRadioButtonsObj;
        lod.redSlider = redSliderObj;
        lod.greenSlider = greenSliderObj;
        lod.blueSlider = blueSliderObj;
        lod.pullSlider = pullSliderObj;
        lod.dampSlider = dampSliderObj;
        lod.wobbleStartSpeedSlider = wobbleStartSpeedSliderObj;
        lod.growStartSlider = growStartSliderObj;
        lod.growEndSlider = growEndSliderObj;
        lod.decaySlider = decaySliderObj;
        loadout[k] = lod;
    }
        
    // Set initial loadout
    initLoadout(currentLetterKey);
    
    // Random button: initLoadout must be called first (to get positioning)
    ButtonData randomButtonData = {};
    randomButtonData.pos = glm::vec2(CONTROL_PANEL_LEFT, decaySlider->pos.y + SLIDER_HEIGHT + CONTROL_PADDING);
    randomButtonData.size = glm::vec2(CONTROL_PANEL_WIDTH, SLIDER_HEIGHT);
    randomButton = new ButtonObject(randomButtonData);
    
    // Init prototype bubble
    initDesignBubble();
    
    /*
     
     Screen change arrows
     
     */
    {
        glm::vec2 arrowScale = glm::vec2(80, 60);
        float arrowPadding = 40.0f;
        
        // Right arrow (bubble screen)
        GeoData rData = {};
        rData.id = RIGHT_ARROW_ID;
        
        float rx = screenWidth - (arrowScale.x + arrowPadding);
        rData.pos = glm::vec2(rx, screenHeight / 2.0f);
        rData.col = glm::vec3(1.0f, 1.0f, 1.0f);
        rData.scale = arrowScale;
        
        fillRightArrowVtx(rData.pts);

        WobbleObject *rObj = new WobbleObject(rData);
        wobbleRenderer->initRenderData(*rObj);
        
        rightArrowObj = rObj;
        
        // Left arrow (design screen)
        GeoData lData = {};
        lData.id = LEFT_ARROW_ID;
        
        float lx = screenWidth + arrowScale.x + arrowPadding;
        lData.pos = glm::vec2(lx, screenHeight / 2.0f);
        lData.col = glm::vec3(1.0f, 1.0f, 1.0f);
        lData.scale = arrowScale;
        
        fillLeftArrowVtx(lData.pts);

        WobbleObject *lObj = new WobbleObject(lData);
        wobbleRenderer->initRenderData(*lObj);
        
        leftArrowObj = lObj;
    }
    
    /*
     
     Controls text and lines
     
     */
    
    unsigned int cpID = 0;
    
    // Top control panel line
    LineSegmentData cpTopLineData = LineSegmentData();
    cpTopLineData.id = cpID;
    ++cpID;
    cpTopLineData.pos = glm::vec2(CONTROL_LABEL_LEFT_LINE, CONTROL_PANEL_TOP_LINE);
    cpTopLineData.col = glm::vec3(1.0f, 1.0f, 1.0f);
    cpTopLineData.scale = glm::vec2(2.0f * screenWidth - CONTROL_LABEL_LEFT_LINE, 1.0f);
    fillLineHorizontalVtx(cpTopLineData.pts);
    LineSegmentObject cpTopLineObj = LineSegmentObject(cpTopLineData);
    controlsTextAndLines.push_back(cpTopLineObj);
    lineSegmentRenderer->initRenderData(cpTopLineObj);
    
    // Left control panel line
    for (auto x: {-3.0f, 0.0f, 3.0f})
    {
        LineSegmentData cpLeftLineData = LineSegmentData();
        cpLeftLineData.id = cpID;
        ++cpID;
        cpLeftLineData.pos = glm::vec2(CONTROL_PANEL_LEFT - CONTROL_PADDING + x, CONTROL_PANEL_TOP_LINE);
        cpLeftLineData.col = glm::vec3(0.3f, 0.3f, 0.3f);
        cpLeftLineData.scale = glm::vec2(1.0f, static_cast<float>(LOGICAL_HEIGHT) - CONTROL_PANEL_TOP_LINE);
        fillLineVerticalVtx(cpLeftLineData.pts);
        LineSegmentObject cpLeftLineObj = LineSegmentObject(cpLeftLineData);
        controlsTextAndLines.push_back(cpLeftLineObj);
        lineSegmentRenderer->initRenderData(cpLeftLineObj);
    }
    
    // Line left of control panel labels
    LineSegmentData labelLeftLineData = LineSegmentData();
    labelLeftLineData.id = cpID;
    ++cpID;
    labelLeftLineData.pos = glm::vec2(CONTROL_LABEL_LEFT_LINE, CONTROL_PANEL_TOP_LINE);
    labelLeftLineData.col = glm::vec3(1.0f, 1.0f, 1.0f);
    labelLeftLineData.scale = glm::vec2(1.0f, static_cast<float>(LOGICAL_HEIGHT) - CONTROL_PANEL_TOP_LINE);
    fillLineVerticalVtx(labelLeftLineData.pts);
    LineSegmentObject labelLeftLineObj = LineSegmentObject(labelLeftLineData);
    controlsTextAndLines.push_back(labelLeftLineObj);
    lineSegmentRenderer->initRenderData(labelLeftLineObj);
    
    // Num sides slider label
    int labelIndex = 1;
    for (auto s: {"s", "t", "p"})
    {
        LineSegmentData labelData = LineSegmentData();
        labelData.id = cpID;
        ++cpID;
        float xOff = (static_cast<float>(labelIndex) * CONTROL_PADDING + static_cast<float>(labelIndex) * LABEL_LETTER_SCALE.x - (LABEL_LETTER_SCALE.x / 2.0f));
        float xPos = CONTROL_PANEL_LEFT_LINE - xOff;
        labelData.pos = glm::vec2(xPos, numSidesSlider->pos.y + SLIDER_HEIGHT / 2.0f);
        labelData.col = glm::vec3(1.0f, 1.0f, 1.0f);
        labelData.scale = LABEL_LETTER_SCALE;
        fillLetterVtx(labelData.pts, s);
        
        LineSegmentObject labelObj = LineSegmentObject(labelData);
        controlsTextAndLines.push_back(labelObj);
        lineSegmentRenderer->initRenderData(labelObj);
        
        ++labelIndex;
    }
    
    // Render mode slider label
    labelIndex = 1;
    for (auto s: {"d", "o", "m"})
    {
        LineSegmentData labelData = LineSegmentData();
        labelData.id = cpID;
        ++cpID;
        float xOff = (static_cast<float>(labelIndex) * CONTROL_PADDING + static_cast<float>(labelIndex) * LABEL_LETTER_SCALE.x - (LABEL_LETTER_SCALE.x / 2.0f));
        float xPos = CONTROL_PANEL_LEFT_LINE - xOff;
        labelData.pos = glm::vec2(xPos, renderModeRadioButtons->pos.y + SLIDER_HEIGHT / 2.0f);
        labelData.col = glm::vec3(1.0f, 1.0f, 1.0f);
        labelData.scale = LABEL_LETTER_SCALE;
        fillLetterVtx(labelData.pts, s);
        
        LineSegmentObject labelObj = LineSegmentObject(labelData);
        controlsTextAndLines.push_back(labelObj);
        lineSegmentRenderer->initRenderData(labelObj);
        
        ++labelIndex;
    }
    
    // Red slider label
    labelIndex = 1;
    for (auto s: {"d", "e", "r"})
    {
        LineSegmentData labelData = LineSegmentData();
        labelData.id = cpID;
        ++cpID;
        float xOff = (static_cast<float>(labelIndex) * CONTROL_PADDING + static_cast<float>(labelIndex) * LABEL_LETTER_SCALE.x - (LABEL_LETTER_SCALE.x / 2.0f));
        float xPos = CONTROL_PANEL_LEFT_LINE - xOff;
        labelData.pos = glm::vec2(xPos, redSlider->pos.y + SLIDER_HEIGHT / 2.0f);
        labelData.col = glm::vec3(1.0f, 1.0f, 1.0f);
        labelData.scale = LABEL_LETTER_SCALE;
        fillLetterVtx(labelData.pts, s);
        
        LineSegmentObject labelObj = LineSegmentObject(labelData);
        controlsTextAndLines.push_back(labelObj);
        lineSegmentRenderer->initRenderData(labelObj);
        
        ++labelIndex;
    }
    
    // Green slider label
    labelIndex = 1;
    for (auto s: {"n", "r", "g"})
    {
        LineSegmentData labelData = LineSegmentData();
        labelData.id = cpID;
        ++cpID;
        float xOff = (static_cast<float>(labelIndex) * CONTROL_PADDING + static_cast<float>(labelIndex) * LABEL_LETTER_SCALE.x - (LABEL_LETTER_SCALE.x / 2.0f));
        float xPos = CONTROL_PANEL_LEFT_LINE - xOff;
        labelData.pos = glm::vec2(xPos, greenSlider->pos.y + SLIDER_HEIGHT / 2.0f);
        labelData.col = glm::vec3(1.0f, 1.0f, 1.0f);
        labelData.scale = LABEL_LETTER_SCALE;
        fillLetterVtx(labelData.pts, s);
        
        LineSegmentObject labelObj = LineSegmentObject(labelData);
        controlsTextAndLines.push_back(labelObj);
        lineSegmentRenderer->initRenderData(labelObj);
        
        ++labelIndex;
    }
    
    // Blue slider label
    labelIndex = 1;
    for (auto s: {"u", "l", "b"})
    {
        LineSegmentData labelData = LineSegmentData();
        labelData.id = cpID;
        ++cpID;
        float xOff = (static_cast<float>(labelIndex) * CONTROL_PADDING + static_cast<float>(labelIndex) * LABEL_LETTER_SCALE.x - (LABEL_LETTER_SCALE.x / 2.0f));
        float xPos = CONTROL_PANEL_LEFT_LINE - xOff;
        labelData.pos = glm::vec2(xPos, blueSlider->pos.y + SLIDER_HEIGHT / 2.0f);
        labelData.col = glm::vec3(1.0f, 1.0f, 1.0f);
        labelData.scale = LABEL_LETTER_SCALE;
        fillLetterVtx(labelData.pts, s);
        
        LineSegmentObject labelObj = LineSegmentObject(labelData);
        controlsTextAndLines.push_back(labelObj);
        lineSegmentRenderer->initRenderData(labelObj);
        
        ++labelIndex;
    }
    
    // Wobble start speed (point mass init vel) slider label
    labelIndex = 1;
    for (auto s: {"r", "t", "s"})
    {
        LineSegmentData labelData = LineSegmentData();
        labelData.id = cpID;
        ++cpID;
        float xOff = (static_cast<float>(labelIndex) * CONTROL_PADDING + static_cast<float>(labelIndex) * LABEL_LETTER_SCALE.x - (LABEL_LETTER_SCALE.x / 2.0f));
        float xPos = CONTROL_PANEL_LEFT_LINE - xOff;
        labelData.pos = glm::vec2(xPos, wobbleStartSpeedSlider->pos.y + SLIDER_HEIGHT / 2.0f);
        labelData.col = glm::vec3(1.0f, 1.0f, 1.0f);
        labelData.scale = LABEL_LETTER_SCALE;
        fillLetterVtx(labelData.pts, s);
        
        LineSegmentObject labelObj = LineSegmentObject(labelData);
        controlsTextAndLines.push_back(labelObj);
        lineSegmentRenderer->initRenderData(labelObj);
        
        ++labelIndex;
    }
    
    // Pull (point mass gravity) slider label
    labelIndex = 1;
    for (auto s: {"l", "u", "p"})
    {
        LineSegmentData labelData = LineSegmentData();
        labelData.id = cpID;
        ++cpID;
        float xOff = (static_cast<float>(labelIndex) * CONTROL_PADDING + static_cast<float>(labelIndex) * LABEL_LETTER_SCALE.x - (LABEL_LETTER_SCALE.x / 2.0f));
        float xPos = CONTROL_PANEL_LEFT_LINE - xOff;
        labelData.pos = glm::vec2(xPos, pullSlider->pos.y + SLIDER_HEIGHT / 2.0f);
        labelData.col = glm::vec3(1.0f, 1.0f, 1.0f);
        labelData.scale = LABEL_LETTER_SCALE;
        fillLetterVtx(labelData.pts, s);
        
        LineSegmentObject labelObj = LineSegmentObject(labelData);
        controlsTextAndLines.push_back(labelObj);
        lineSegmentRenderer->initRenderData(labelObj);
        
        ++labelIndex;
    }
    
    // Pull (point mass gravity) slider label
    labelIndex = 1;
    for (auto s: {"p", "m", "d"})
    {
        LineSegmentData labelData = LineSegmentData();
        labelData.id = cpID;
        ++cpID;
        float xOff = (static_cast<float>(labelIndex) * CONTROL_PADDING + static_cast<float>(labelIndex) * LABEL_LETTER_SCALE.x - (LABEL_LETTER_SCALE.x / 2.0f));
        float xPos = CONTROL_PANEL_LEFT_LINE - xOff;
        labelData.pos = glm::vec2(xPos, dampSlider->pos.y + SLIDER_HEIGHT / 2.0f);
        labelData.col = glm::vec3(1.0f, 1.0f, 1.0f);
        labelData.scale = LABEL_LETTER_SCALE;
        fillLetterVtx(labelData.pts, s);
        
        LineSegmentObject labelObj = LineSegmentObject(labelData);
        controlsTextAndLines.push_back(labelObj);
        lineSegmentRenderer->initRenderData(labelObj);
        
        ++labelIndex;
    }
    
    // Size start (grow) slider label
    labelIndex = 1;
    for (auto s: {"s", "z", "s"})
    {
        LineSegmentData labelData = LineSegmentData();
        labelData.id = cpID;
        ++cpID;
        float xOff = (static_cast<float>(labelIndex) * CONTROL_PADDING + static_cast<float>(labelIndex) * LABEL_LETTER_SCALE.x - (LABEL_LETTER_SCALE.x / 2.0f));
        float xPos = CONTROL_PANEL_LEFT_LINE - xOff;
        labelData.pos = glm::vec2(xPos, growStartSlider->pos.y + SLIDER_HEIGHT / 2.0f);
        labelData.col = glm::vec3(1.0f, 1.0f, 1.0f);
        labelData.scale = LABEL_LETTER_SCALE;
        fillLetterVtx(labelData.pts, s);
        
        LineSegmentObject labelObj = LineSegmentObject(labelData);
        controlsTextAndLines.push_back(labelObj);
        lineSegmentRenderer->initRenderData(labelObj);
        
        ++labelIndex;
    }
    
    // Size end (grow) slider label
    labelIndex = 1;
    for (auto s: {"e", "z", "s"})
    {
        LineSegmentData labelData = LineSegmentData();
        labelData.id = cpID;
        ++cpID;
        float xOff = (static_cast<float>(labelIndex) * CONTROL_PADDING + static_cast<float>(labelIndex) * LABEL_LETTER_SCALE.x - (LABEL_LETTER_SCALE.x / 2.0f));
        float xPos = CONTROL_PANEL_LEFT_LINE - xOff;
        labelData.pos = glm::vec2(xPos, growEndSlider->pos.y + SLIDER_HEIGHT / 2.0f);
        labelData.col = glm::vec3(1.0f, 1.0f, 1.0f);
        labelData.scale = LABEL_LETTER_SCALE;
        fillLetterVtx(labelData.pts, s);
        
        LineSegmentObject labelObj = LineSegmentObject(labelData);
        controlsTextAndLines.push_back(labelObj);
        lineSegmentRenderer->initRenderData(labelObj);
        
        ++labelIndex;
    }
    
    // Decay slider label
    labelIndex = 1;
    for (auto s: {"y", "c", "d"})
    {
        LineSegmentData labelData = LineSegmentData();
        labelData.id = cpID;
        ++cpID;
        float xOff = (static_cast<float>(labelIndex) * CONTROL_PADDING + static_cast<float>(labelIndex) * LABEL_LETTER_SCALE.x - (LABEL_LETTER_SCALE.x / 2.0f));
        float xPos = CONTROL_PANEL_LEFT_LINE - xOff;
        labelData.pos = glm::vec2(xPos, decaySlider->pos.y + SLIDER_HEIGHT / 2.0f);
        labelData.col = glm::vec3(1.0f, 1.0f, 1.0f);
        labelData.scale = LABEL_LETTER_SCALE;
        fillLetterVtx(labelData.pts, s);
        
        LineSegmentObject labelObj = LineSegmentObject(labelData);
        controlsTextAndLines.push_back(labelObj);
        lineSegmentRenderer->initRenderData(labelObj);
        
        ++labelIndex;
    }
    
    // Random button label
    labelIndex = 1;
    for (auto s: {"d", "n", "r"})
    {
        LineSegmentData labelData = LineSegmentData();
        labelData.id = cpID;
        ++cpID;
        float xOff = (static_cast<float>(labelIndex) * CONTROL_PADDING + static_cast<float>(labelIndex) * LABEL_LETTER_SCALE.x - (LABEL_LETTER_SCALE.x / 2.0f));
        float xPos = CONTROL_PANEL_LEFT_LINE - xOff;
        labelData.pos = glm::vec2(xPos, randomButton->pos.y + SLIDER_HEIGHT / 2.0f);
        labelData.col = glm::vec3(1.0f, 1.0f, 1.0f);
        labelData.scale = LABEL_LETTER_SCALE;
        fillLetterVtx(labelData.pts, s);
        
        LineSegmentObject labelObj = LineSegmentObject(labelData);
        controlsTextAndLines.push_back(labelObj);
        lineSegmentRenderer->initRenderData(labelObj);
        
        ++labelIndex;
    }
}

void Game::initDesignBubble()
{
    // Clear flag and delete old prototype design bubble object
    designUpdate = false;
    if (designBubble != nullptr)
    {
        wobbleRenderer->deleteData(*designBubble);
        delete designBubble;
    }
    
    // Build new prototype design bubble object
    WobbleData wd = {};
    wd.id = DESIGN_BUBBLE_ID;
    
    float px = static_cast<float>(LOGICAL_WIDTH) + (CONTROL_LABEL_LEFT_LINE - static_cast<float>(LOGICAL_WIDTH)) / 2.0f;
    float py = static_cast<float>(LOGICAL_HEIGHT) / 2.0f;
    wd.pos = glm::vec2(px, py);
    
    wd.renderMode = WobbleRenderMode(renderModeRadioButtons->selectedButton);
    wd.res = numSidesSlider->val;
    wd.radStart = growStartSlider->normVal() * RAD_START_MAX;
    wd.radEnd = growEndSlider->normVal() * RAD_END_MAX;
    wd.life = static_cast<int>(decaySlider->normVal() * LIFE_MAX);
    wd.vel = glm::vec2(0.0f, 0.0f);
    
    float r = redSlider->normVal();
    float g = greenSlider->normVal();
    float b = blueSlider->normVal();
    wd.col = glm::vec3(r, g, b);
    
    wd.pull = pullSlider->normVal() * PULL_MAX;
    wd.damp = dampSlider->normVal() * DAMP_MAX;
    wd.wobbleStartSpeed = wobbleStartSpeedSlider->normVal() * WOBBLE_START_SPEED_MAX;
    
    WobbleObject *bub = new WobbleObject(wd);
    wobbleRenderer->initRenderData(*bub);
    
    designBubble = bub;
}

void Game::initLoadout(std::string letterKey)
{
    // Clear flag and delete old letter object
    currentLetterUpdate = NO_LETTER_UPDATE;
    if (currentLetterObj != nullptr)
    {
        wobbleRenderer->deleteData(*currentLetterObj);
        delete currentLetterObj;
    }
    
    // Build new letter object
    GeoData ld = {};
    ld.id = CURRENT_LETTER_ID;
    
    float px = CONTROL_PANEL_LEFT + CONTROL_PANEL_WIDTH / 2.0f;
    ld.pos = glm::vec2(px, LOADOUT_LETTER_CENTER);
    ld.col = glm::vec3(1.0f, 1.0f, 1.0f);
    ld.scale = glm::vec2(LOADOUT_LETTER_HEIGHT / 2.0f, LOADOUT_LETTER_HEIGHT / 2.0f);
    
    fillLetterVtx(ld.pts, letterKey);

    WobbleObject *letterObj = new WobbleObject(ld);
    wobbleRenderer->initRenderData(*letterObj);
    
    currentLetterObj = letterObj;
    
    // Save off old controls
    if (numSidesSlider != nullptr)
    {
        loadout[currentLetterKey].numSidesSlider = numSidesSlider;
        loadout[currentLetterKey].renderModeRadioButtons = renderModeRadioButtons;
        loadout[currentLetterKey].redSlider = redSlider;
        loadout[currentLetterKey].greenSlider = greenSlider;
        loadout[currentLetterKey].blueSlider = blueSlider;
        loadout[currentLetterKey].pullSlider = pullSlider;
        loadout[currentLetterKey].dampSlider = dampSlider;
        loadout[currentLetterKey].wobbleStartSpeedSlider = wobbleStartSpeedSlider;
        loadout[currentLetterKey].growStartSlider = growStartSlider;
        loadout[currentLetterKey].growEndSlider = growEndSlider;
        loadout[currentLetterKey].decaySlider = decaySlider;
    }

    currentLetterKey = letterKey;
    
    // Update current controls
    numSidesSlider = loadout[letterKey].numSidesSlider;
    renderModeRadioButtons = loadout[letterKey].renderModeRadioButtons;
    redSlider = loadout[letterKey].redSlider;
    greenSlider = loadout[letterKey].greenSlider;
    blueSlider = loadout[letterKey].blueSlider;
    pullSlider = loadout[letterKey].pullSlider;
    dampSlider = loadout[letterKey].dampSlider;
    wobbleStartSpeedSlider = loadout[letterKey].wobbleStartSpeedSlider;
    growStartSlider = loadout[letterKey].growStartSlider;
    growEndSlider = loadout[letterKey].growEndSlider;
    decaySlider = loadout[letterKey].decaySlider;
}

void Game::close()
{
    // TODO: properly delete all stuff
    
    teardownInput();
    
    ResourceManager::Clear();
    
//    delete spriteRenderer;
    delete wobbleRenderer;
    delete sliderRenderer;
    delete radioButtonRenderer;
    delete buttonRenderer;
    delete lineSegmentRenderer;
    
    // Window
    closeGL();

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    
    //Quit SDL subsystems
    SDL_Quit();
    
    SDL_GL_DeleteContext(gOpenGLContext);
}

void Game::randomizeLoadout(std::string letterKey)
{
    loadout[letterKey].numSidesSlider->randomize();
    loadout[letterKey].renderModeRadioButtons->randomize();
    loadout[letterKey].redSlider->randomize();
    loadout[letterKey].greenSlider->randomize();
    loadout[letterKey].blueSlider->randomize();
    loadout[letterKey].pullSlider->randomize();
    loadout[letterKey].dampSlider->randomize();
    loadout[letterKey].wobbleStartSpeedSlider->randomize();
    loadout[letterKey].growStartSlider->randomize();
    loadout[letterKey].growEndSlider->randomize();
    loadout[letterKey].decaySlider->randomize();
}

void Game::randomizeAllLoadouts()
{
    for (auto k: LOADOUT_KEYS)
    {
        randomizeLoadout(k);
    }
    
    designUpdate = true;
}
