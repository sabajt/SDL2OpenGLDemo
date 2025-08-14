//
//  RadioButtonRenderer.cpp
//  GameEngine
//
//  Created by John Saba on 2/17/25.
//

#include "RadioButtonRenderer.hpp"
#include "Constants.h"
#include "Game.h"
#include "Lerp.h"

RadioButtonRenderer::RadioButtonRenderer(const GLShader &shader)
{
    this->shader = shader;
    
    glGenVertexArrays(1, &vao);
}

RadioButtonRenderer::~RadioButtonRenderer()
{
    glDeleteVertexArrays(1, &this->vao);
}

void RadioButtonRenderer::initRenderData()
{
    float vertices[] = 
    {
        // Filled in button
        0.0f, 1.0f, // bottom left
        1.0f, 0.0f, // top right
        0.0f, 0.0f, // top left

        0.0f, 1.0f, // bottom left
        1.0f, 1.0f, // bottom right
        1.0f, 0.0f, // top right
        
        // Outlined button
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
void RadioButtonRenderer::render(Game &game, double dt, RadioButtonObject &obj)
{
    shader.use();
    shader.setFloat("alpha", 1.0f);
    shader.setVec3("color", obj.col);
    shader.setInt("renderType", RT_PASSTHRU);

    // scale, rotate, translate but needs to be reversed so translate first
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-lerp(game.lastCamera, game.camera, dt), 0.0f));
    model = glm::translate(model, glm::vec3(obj.pos, 0.0f));
    
    glBindVertexArray(vao);
        
    for (int i = 0; i < obj.numButtons; ++i)
    {
        float x = (float(i) * obj.buttonSize.x) + (float(i) * obj.buttonPadding);
        glm::mat4 buttonModel = glm::translate(model, glm::vec3(x, 0.0f, 0.0f));

        buttonModel = glm::scale(buttonModel, glm::vec3(obj.buttonSize, 1.0f));
        shader.setMat4("model", buttonModel);
        
        if (i == obj.selectedButton)
        {
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }
        else
        {
            glDrawArrays(GL_LINE_LOOP, 6, sizeof(float) * 4);
        }
    }

    glBindVertexArray(0);
}
