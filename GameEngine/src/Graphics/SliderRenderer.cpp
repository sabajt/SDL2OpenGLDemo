//
//  SliderRenderer.cpp
//  GameEngine
//
//  Created by John Saba on 2/15/25.
//

#include "SliderRenderer.hpp"
#include "Constants.h"
#include "Game.h"
#include "Lerp.h"

SliderRenderer::SliderRenderer(const GLShader &shader)
{
    this->shader = shader;
    
    glGenVertexArrays(1, &vao);
}

SliderRenderer::~SliderRenderer()
{
    glDeleteVertexArrays(1, &this->vao);
}

void SliderRenderer::initRenderData()
{
    float vertices[] = 
    {
        // Quad
        0.0f, 1.0f, // bottom left
        1.0f, 0.0f, // top right
        0.0f, 0.0f, // top left

        0.0f, 1.0f, // bottom left
        1.0f, 1.0f, // bottom right
        1.0f, 0.0f, // top right
        
        // Outline rect
        0.0f, 1.0f, // bottom left
        1.0f, 1.0f, // bottom right
        1.0f, 0.0f, // top right
        0.0f, 0.0f, // top left

    };
    
    GLuint vbo;
    glGenBuffers(1, &vbo);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0); // location 0 of shader
    
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

// TODO: might not need dt if no animation
void SliderRenderer::render(Game &game, double dt, SliderObject &sliderObject)
{
    shader.use();
    shader.setFloat("alpha", 1.0f);
    shader.setVec3("color", sliderObject.col);
    shader.setInt("renderType", RT_PASSTHRU);
    
    // scale, rotate, translate but needs to be reversed so translate first
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-lerp(game.lastCamera, game.camera, dt), 0.0f));
    model = glm::translate(model, glm::vec3(sliderObject.pos, 0.0f));
    
    // Render outline rect (range)

    glm::mat4 outlineModel = glm::scale(model, glm::vec3(sliderObject.size, 1.0f));
    shader.setMat4("model", outlineModel);
    
    glBindVertexArray(vao);
    glDrawArrays(GL_LINE_LOOP, 6, sizeof(float) * 4);
    
    // Render filled in quad (value)

    glm::mat4 valueModel = glm::scale(model, glm::vec3(sliderObject.valSize, 1.0f));
    shader.setMat4("model", valueModel);
    
//    glEnableVertexAttribArray(0); // loc 0 (needed?)
//    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    
    glDrawArrays(GL_TRIANGLES, 0, 6);

//    glBindBuffer(GL_ARRAY_BUFFER, 0); // needed?
    glBindVertexArray(0);
}

