//
//  LineSegmentRenderer.cpp
//  GameEngine
//
//  Created by John Saba on 2/23/25.
//

#include "LineSegmentRenderer.hpp"
#include "Lerp.h"
#include "Constants.h"
#include "Game.h"

LineSegmentRenderer::LineSegmentRenderer(const GLShader &shader)
{
    this->shader = shader;
    
    glGenVertexArrays(1, &vao);
}

LineSegmentRenderer::~LineSegmentRenderer()
{
    glDeleteVertexArrays(1, &this->vao);
}

void LineSegmentRenderer::deleteData(const LineSegmentObject &lineSegmentObject)
{
    GLuint vbo = idVboMap[lineSegmentObject.id];
    glDeleteBuffers(1, &vbo);
}

void LineSegmentRenderer::initRenderData(const LineSegmentObject &lineSegmentObject)
{
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0); // location 0 of shader

    GLuint vbo;
    glGenBuffers(1, &vbo);
    idVboMap[lineSegmentObject.id] = vbo;

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    size_t verticesLength = (lineSegmentObject.points.size() * 2);
    float vertices[verticesLength];
    
    fillVertices(lineSegmentObject.points, vertices);
    
    glBufferData(GL_ARRAY_BUFFER, verticesLength * sizeof(float), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void LineSegmentRenderer::render(Game &game, double dt, LineSegmentObject &lineSegmentObject)
{
    shader.use();
    shader.setFloat("alpha", 1.0f);
    shader.setVec3("color", lineSegmentObject.col);
    shader.setInt("renderType", RT_PASSTHRU);
    
    GLuint vbo = idVboMap[lineSegmentObject.id];
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindVertexArray(vao);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    
    // scale, rotate, translate (reversed)
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-lerp(game.lastCamera, game.camera, dt), 0.0f));
    model = glm::translate(model, glm::vec3(lineSegmentObject.pos, 0.0f));
    
    shader.setMat4("model", model);
    
    glDrawArrays(GL_LINE_STRIP, 0, GLsizei(lineSegmentObject.points.size()));
    
    glBindVertexArray(0);
}

void LineSegmentRenderer::fillVertices(const std::vector<glm::vec2> &points, float vertices[])
{
    unsigned int i = 0;
    for (auto &p: points)
    {
        vertices[i] = p.x;
        ++i;
        vertices[i] = p.y;
        ++i;
    }
}
