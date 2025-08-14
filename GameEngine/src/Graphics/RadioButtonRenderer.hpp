//
//  RadioButtonRenderer.hpp
//  GameEngine
//
//  Created by John Saba on 2/17/25.
//

#ifndef RadioButtonRenderer_hpp
#define RadioButtonRenderer_hpp

#include "GLShader.h"
#include "RadioButtonObject.hpp"

class Game;

class RadioButtonRenderer
{
public:
    RadioButtonRenderer(const GLShader &shader);
    ~RadioButtonRenderer();

    void initRenderData();
    void render(Game &game, double dt, RadioButtonObject &radioButtonObject);
    
private:
    GLShader shader;
    GLuint vao;
};

#endif /* RadioButtonRenderer_hpp */
