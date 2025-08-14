//
//  ButtonRenderer.cpp
//  GameEngine
//
//  Created by John Saba on 2/24/25.
//

#include "ButtonRenderer.hpp"
#include "Constants.h"
#include "Game.h"
#include "Lerp.h"

ButtonRenderer::ButtonRenderer(const GLShader &shader)
{
    this->shader = shader;
    
    glGenVertexArrays(1, &vao);
}

ButtonRenderer::~ButtonRenderer()
{
    glDeleteVertexArrays(1, &this->vao);
}

void ButtonRenderer::initRenderData()
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

void ButtonRenderer::render(Game &game, double dt, ButtonObject &buttonObject)
{
    shader.use();
    shader.setFloat("alpha", 1.0f);
    shader.setVec3("color", buttonObject.col);
    shader.setInt("renderType", RT_PASSTHRU);
    
    // Scale, rotate, translate but needs to be reversed so translate first
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-lerp(game.lastCamera, game.camera, dt), 0.0f));
    model = glm::translate(model, glm::vec3(buttonObject.pos, 0.0f));
    
    // Render outline rect (range)

    glm::mat4 outlineModel = glm::scale(model, glm::vec3(buttonObject.size, 1.0f));
    shader.setMat4("model", outlineModel);
    
    glBindVertexArray(vao);
    glDrawArrays(GL_LINE_LOOP, 6, sizeof(float) * 4);
    
    // Render flashing button state quad
    if (buttonObject.alpha < 1.0f)
    {
        glm::mat4 pressedModel = glm::scale(model, glm::vec3(buttonObject.size, 1.0f));
        shader.setFloat("alpha", buttonObject.alpha);
        shader.setMat4("model", pressedModel);
        
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    glBindVertexArray(0);
}
