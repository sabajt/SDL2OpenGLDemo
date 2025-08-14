//
//  LineSegmentRenderer.hpp
//  GameEngine
//
//  Created by John Saba on 2/23/25.
//

#ifndef LineSegmentRenderer_hpp
#define LineSegmentRenderer_hpp

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <map>
#include "GLShader.h"
#include "LineSegmentObject.hpp"

class Game;

class LineSegmentRenderer
{
public:
    LineSegmentRenderer(const GLShader &shader);
    ~LineSegmentRenderer();

    void initRenderData(const LineSegmentObject &lineSegmentObject);
    void render(Game &game, double dt, LineSegmentObject &lineSegmentObject);
    void deleteData(const LineSegmentObject &lineSegmentObject);
    void fillVertices(const std::vector<glm::vec2> &points, float vertices[]);

private:
    GLShader shader;
    GLuint vao;
    std::map<unsigned int, GLuint> idVboMap;
};
#endif /* LineSegmentRenderer_hpp */
