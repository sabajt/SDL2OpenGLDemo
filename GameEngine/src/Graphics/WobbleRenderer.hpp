//
//  WobbleRenderer.hpp
//  GameEngine
//
//  Created by John Saba on 1/24/25.
//

#ifndef WobbleRenderer_hpp
#define WobbleRenderer_hpp

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <map>
#include "GLShader.h"
#include "WobbleObject.hpp"

class Game;

class WobbleRenderer
{
public:
    WobbleRenderer(const GLShader &shader);
    ~WobbleRenderer();

    void initRenderData(const WobbleObject &wobbleObject);
    void render(Game &game, double dt, WobbleObject &wobbleObject);
    void deleteData(const WobbleObject &wobbleObject);
    
private:
    GLShader shader;
    GLuint vao;
    std::map<unsigned int, GLuint> idVboMap;
    std::map<unsigned int, GLuint> idEboMap;
    
    void fillVertices(double dt, const std::vector<PointMass> &points, float vertices[]);
    void fillIndices(unsigned int indices[], size_t indicesLength);
};

#endif /* WobbleRenderer_hpp */
