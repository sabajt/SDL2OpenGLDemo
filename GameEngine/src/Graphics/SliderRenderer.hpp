//
//  SliderRenderer.hpp
//  GameEngine
//
//  Created by John Saba on 2/15/25.
//

#ifndef SliderRenderer_hpp
#define SliderRenderer_hpp

#include "GLShader.h"
#include "SliderObject.hpp"

class Game;

class SliderRenderer
{
public:
    SliderRenderer(const GLShader &shader);
    ~SliderRenderer();

    void initRenderData();
    void render(Game &game, double dt, SliderObject &sliderObject);
    
private:
    GLShader shader;
    GLuint vao;
};
#endif /* SliderRenderer_hpp */
