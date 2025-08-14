//
//  ButtonRenderer.hpp
//  GameEngine
//
//  Created by John Saba on 2/24/25.
//

#ifndef ButtonRenderer_hpp
#define ButtonRenderer_hpp

#include "GLShader.h"
#include "ButtonObject.hpp"

class Game;

class ButtonRenderer
{
public:
    ButtonRenderer(const GLShader &shader);
    ~ButtonRenderer();

    void initRenderData();
    void render(Game &game, double dt, ButtonObject &buttonObject);
    
private:
    GLShader shader;
    GLuint vao;
};
#endif /* ButtonRenderer_hpp */
