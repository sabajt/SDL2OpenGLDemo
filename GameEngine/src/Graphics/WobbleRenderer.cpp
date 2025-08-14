//
//  ShapeRenderer.cpp
//  GameEngine
//
//  Created by John Saba on 1/24/25.
//

#include "WobbleRenderer.hpp"
#include "Lerp.h"
#include "Constants.h"
#include "Game.h"

WobbleRenderer::WobbleRenderer(const GLShader &shader)
{
    this->shader = shader;   
    
    glGenVertexArrays(1, &vao);
}

WobbleRenderer::~WobbleRenderer()
{
    glDeleteVertexArrays(1, &this->vao);
}

void WobbleRenderer::deleteData(const WobbleObject &wobbleObject)
{
    GLuint vbo = idVboMap[wobbleObject.id];
    glDeleteBuffers(1, &vbo);
}

void WobbleRenderer::initRenderData(const WobbleObject &wobbleObject)
{
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0); // location 0 of shader

    GLuint vbo;
    glGenBuffers(1, &vbo);
    idVboMap[wobbleObject.id] = vbo;
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    // TODO: could optimize by having 1 vbo for all particle mode rendering since vertices don't change
    if (wobbleObject.renderMode == RENDER_MODE_SDF_PARTICLE)
    {
        float vertices[] =
        {
            0.0f, 1.0f, // bottom left
            1.0f, 0.0f, // top right
            0.0f, 0.0f, // top left
            0.0f, 1.0f, // bottom left
            1.0f, 1.0f, // bottom right
            1.0f, 0.0f, // top right
        };
        
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        
        return;
    }
    
    // ---------------------------
    // Render modes line, or solid
    
    size_t verticesLength = (wobbleObject.points.size() * 2) + 2;
    float vertices[verticesLength];
    vertices[0] = 0.0f;
    vertices[1] = 0.0f;
    fillVertices(1.0f, wobbleObject.points, vertices);
    
    glBufferData(GL_ARRAY_BUFFER, verticesLength * sizeof(float), vertices, GL_DYNAMIC_DRAW);
    
    if (wobbleObject.renderMode == RENDER_MODE_SOLID ||
        wobbleObject.renderMode == RENDER_MODE_GRADIENT ||
        wobbleObject.renderMode == RENDER_MODE_COOL)
    {
        size_t indicesLength = wobbleObject.points.size() * 3;
        unsigned int indices[indicesLength];
        fillIndices(indices, indicesLength);
        unsigned int ebo;
        glGenBuffers(1, &ebo);
        idEboMap[wobbleObject.id] = ebo;
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);
    }
    
    // If the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride (4th param) 
    // to let OpenGL figure it out
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void WobbleRenderer::render(Game &game, double dt, WobbleObject &wobbleObject)
{
    shader.use();
    shader.setFloat("alpha", wobbleObject.alpha);
    shader.setVec3("color", wobbleObject.col);
    
    GLuint vbo = idVboMap[wobbleObject.id];
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindVertexArray(vao);
//    glEnableVertexAttribArray(0); // loc 0 (needed?)
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

    glm::vec2 objPos = lerp(wobbleObject.lastPos, wobbleObject.pos, dt);
    
    // scale, rotate, translate (reversed)
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-lerp(game.lastCamera, game.camera, dt), 0.0f));
    model = glm::translate(model, glm::vec3(objPos, 0.0f));

    if (wobbleObject.renderMode == RENDER_MODE_SDF_PARTICLE)
    {
        shader.setInt("renderType", RT_CIRCLE);
        
        for (PointMass &p: wobbleObject.points)
        {
            glm::vec2 pointPos = lerp(p.lastPos, p.pos, dt);
            glm::mat4 pointModel = glm::translate(model, glm::vec3(pointPos, 0.0f));
            
            pointModel = glm::scale(pointModel, glm::vec3(10.0f, 10.0f, 0.0f));
            
            shader.setMat4("model", pointModel);

            glDrawArrays(GL_TRIANGLES, 0, 6);
        }
        
        glBindVertexArray(0);

        return;
    }
    
    // ---------------------------
    // Render modes line, or solid
    
    shader.setMat4("model", model);
    
    size_t verticesLength = (wobbleObject.points.size() * 2) + 2;
    float vertices[verticesLength];
    vertices[0] = 0.0f;
    vertices[1] = 0.0f;
    fillVertices(dt, wobbleObject.points, vertices);
    
    glBufferSubData(GL_ARRAY_BUFFER, 0 * sizeof(float), verticesLength * sizeof(float), vertices);
    
    if (wobbleObject.renderMode == RENDER_MODE_LINE)
    {
        shader.setInt("renderType", RT_PASSTHRU);

        // Start at 1 (second param) to ignore the middle point in line mode
        glDrawArrays(GL_LINE_LOOP, 1, GLsizei(wobbleObject.points.size()));
    }
    else 
    {
        if (wobbleObject.renderMode == RENDER_MODE_GRADIENT)
        {
            shader.setInt("renderType", RT_GRAD);
        }
        else if (wobbleObject.renderMode == RENDER_MODE_COOL)
        {
            shader.setFloat("time", wobbleObject.t / 600.0f);
            shader.setInt("renderType", RT_COOL);
        }
        else
        {
            shader.setInt("renderType", RT_PASSTHRU);
        }
        
        GLuint ebo = idEboMap[wobbleObject.id];
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        
        size_t indicesLength = wobbleObject.points.size() * 3;
        glDrawElements(GL_TRIANGLES, GLsizei(indicesLength), GL_UNSIGNED_INT, 0);
    }
    
    glBindVertexArray(0);
}

void WobbleRenderer::fillVertices(double dt, const std::vector<PointMass> &points, float vertices[])
{
    unsigned int i = 2;
    for (auto &p: points)
    {
        vertices[i] = lerp(p.lastPos.x, p.pos.x, dt);
        ++i;
        vertices[i] = lerp(p.lastPos.y, p.pos.y, dt);
        ++i;
    }    
}

void WobbleRenderer::fillIndices(unsigned int indices[], size_t indicesLength)
{
    /*
     
     e.g. 4 sides would create...
     TODO: Use triangle fan instead?
     
     1, 0, 2,
     2, 0, 3,
     3, 0, 4
     4, 0, 1
     
     */
    
    int i = 0;
    int j = 1;
    while (i < indicesLength)
    {
        indices[i] = j;
        
        ++i;
        indices[i] = 0;
        
        ++i;
        if (i == (indicesLength - 1))
        {
            indices[i] = 1;
        }
        else
        {
            ++j;
            indices[i] = j;
        }
        
        ++i;
    }
}

