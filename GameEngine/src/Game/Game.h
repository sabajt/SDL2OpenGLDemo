//
//  Game.h
//  GameEngine
//
//  Created by John Saba on 6/23/24.
//

#ifndef Game_h
#define Game_h

#include <SDL2/SDL.h>
#include <string>
#include <map>
#include <memory.h>
#include "GLShader.h"
#include "Command.h"
#include "WobbleRenderer.hpp"
#include "SliderRenderer.hpp"
#include "RadioButtonRenderer.hpp"
#include "ButtonRenderer.hpp"
#include "LineSegmentRenderer.hpp"

// TODO: Do these have to be inline? Why are they here anyway?
// OpenGL Renderering
inline SDL_Window* gWindow = NULL;
inline SDL_GLContext gOpenGLContext = NULL;

inline SliderRenderer *sliderRenderer;
inline RadioButtonRenderer *radioButtonRenderer;
inline ButtonRenderer *buttonRenderer;
inline WobbleRenderer *wobbleRenderer;
inline LineSegmentRenderer *lineSegmentRenderer;

// SDL Input
inline SDL_Joystick* gJoystick = NULL;

enum GameState
{
    GAME_STATE_BUBBLES = 0,
    GAME_STATE_T_BEGIN_BUBBLES_DESIGN,
    GAME_STATE_T_BUBBLES_DESIGN,
    GAME_STATE_DESIGN,
    GAME_STATE_T_BEGIN_DESIGN_BUBBLES,
    GAME_STATE_T_DESIGN_BUBBLES
};

const glm::vec2 GLM_VEC2_NONE = glm::vec2(MAXFLOAT, MAXFLOAT);

struct LoadoutData
{
    SliderObject *numSidesSlider = nullptr;
    RadioButtonObject *renderModeRadioButtons = nullptr;
    SliderObject *redSlider = nullptr;
    SliderObject *greenSlider = nullptr;
    SliderObject *blueSlider = nullptr;
    SliderObject *pullSlider = nullptr;
    SliderObject *dampSlider = nullptr;
    SliderObject *wobbleStartSpeedSlider = nullptr;
    SliderObject *growStartSlider = nullptr;
    SliderObject *growEndSlider = nullptr;
    SliderObject *decaySlider = nullptr;
};

class Game {
public:
    // Use aspect ratio 320/180 for typical wide monitor depth
    // Big monitor -> 2048, 1152
    // Ratio window -> 960, 540
//    static constexpr int LOGICAL_WIDTH = 2048;
//    static constexpr int LOGICAL_HEIGHT = 1152;
//    static constexpr int LOGICAL_WIDTH = 960;
//    static constexpr int LOGICAL_HEIGHT = 540;
    
    // At some point macbook window resolution became:
    static constexpr int LOGICAL_WIDTH = 1352;
    static constexpr int LOGICAL_HEIGHT = 878;
    
    // Control panel layout
    static constexpr glm::vec2 LABEL_LETTER_SCALE = glm::vec2(8.0f, 8.0f);
    static constexpr float LOADOUT_LETTER_HEIGHT = 40.0f;
    static constexpr float LOADOUT_LETTER_CENTER = 40.0f + LOADOUT_LETTER_HEIGHT / 2.0f;
    static constexpr float SLIDER_HEIGHT = 40.0f;
    static constexpr float CONTROL_PADDING = 18.0f;
    static constexpr float CONTROL_PANEL_WIDTH = 300.0f;
    static constexpr float CONTROL_PANEL_TOP_LINE = 2.0f * LOADOUT_LETTER_CENTER;
    static constexpr float CONTROL_PANEL_LEFT = 2.0f * float(LOGICAL_WIDTH) - (CONTROL_PANEL_WIDTH + CONTROL_PADDING);
    static constexpr float CONTROL_PANEL_LEFT_LINE = CONTROL_PANEL_LEFT - CONTROL_PADDING;
    static constexpr float CONTROL_LABEL_LEFT_LINE = CONTROL_PANEL_LEFT_LINE - (4.0f * CONTROL_PADDING + 3.0f * LABEL_LETTER_SCALE.x);
    
    // IDs
    static constexpr unsigned int DESIGN_BUBBLE_ID = 0;
    static constexpr unsigned int CURRENT_LETTER_ID = 1;
    static constexpr unsigned int RIGHT_ARROW_ID = 2;
    static constexpr unsigned int LEFT_ARROW_ID = 3;
    unsigned int currentBubbleId = 4;

    // Bubble config constants
    static constexpr float PULL_MAX = 4.0f;
    static constexpr float WOBBLE_START_SPEED_MAX = 20.0f;
    static constexpr float RAD_START_MAX = 600.0f;
    static constexpr float RAD_END_MAX = 1000.0f;
    static constexpr float LIFE_MAX = 60.0f * 6.0f;
    static constexpr float DAMP_MAX = 0.2f;

    const std::string NO_LETTER_UPDATE = "NONE";
    const std::string NO_BUBBLE_UPDATE = "NONE";

    bool init();
    void handleInput();
    void update(Uint64 ticks);
    void render(double dt);
    void close();
    
    // Lifecycle
    bool quitGame = false;
    GameState gameState = GAME_STATE_BUBBLES;
    
    // Camera
    glm::vec2 camera = glm::vec2(0.0f, 0.0f);
    glm::vec2 lastCamera = glm::vec2(0.0f, 0.0f);
    
    // Screen transitions
    float transitionBeginT = 0.0f;
    
    // Input
    SDL_GameController *controller1 = nullptr;
    std::map<std::string, Command*> inputCommands; // TODO: should commands be pointers? prob not but how?
    glm::vec2 selectedPos = GLM_VEC2_NONE;
    bool shake = false;
    
    // Bubs
    std::vector<WobbleObject> bubs;
    std::string createBubble = NO_BUBBLE_UPDATE;
    
    // Design prototype bubble
    bool designUpdate = false;
    WobbleObject *designBubble = nullptr;
    
    std::string currentLetterUpdate = NO_LETTER_UPDATE;
    std::string currentLetterKey = "z";
    WobbleObject *currentLetterObj = nullptr;
    
    // Controls
    SliderObject *numSidesSlider = nullptr;
    RadioButtonObject *renderModeRadioButtons = nullptr;
    SliderObject *redSlider = nullptr;
    SliderObject *greenSlider = nullptr;
    SliderObject *blueSlider = nullptr;
    SliderObject *pullSlider = nullptr;
    SliderObject *dampSlider = nullptr;
    SliderObject *wobbleStartSpeedSlider = nullptr;
    SliderObject *growStartSlider = nullptr;
    SliderObject *growEndSlider = nullptr;
    SliderObject *decaySlider = nullptr;
    ButtonObject *randomButton = nullptr; // Not part of loadout

    // Controls text and lines
    std::vector<LineSegmentObject> controlsTextAndLines;
    
    // Bubble loadout
    std::map<std::string, LoadoutData> loadout;
    
    // Arrows
    WobbleObject *rightArrowObj = nullptr;
    WobbleObject *leftArrowObj = nullptr;
    
private:
    void initObjects();
    void initDesignBubble();
    void initLoadout(std::string letterKey);
    
    void randomizeLoadout(std::string letterKey);
    void randomizeAllLoadouts();

    // Input Handling
    void setupInput();
    void teardownInput();
    
    // OpenGL
    bool initContextGL();
    void closeGL();
};

#endif /* Game_h */
