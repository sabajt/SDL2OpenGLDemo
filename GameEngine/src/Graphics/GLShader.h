//
//  GLShader.h
//  GameEngine
//
//  Created by John Saba on 9/1/24.
//

#ifndef GLShader_h
#define GLShader_h

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "GLDebug.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class GLShader
{
public:
    GLuint program;
    
    GLShader() {};

    GLShader(const char* vShaderCode, const char* fShaderCode, const char* gShaderCode)
    {
        // compile shaders
        GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        GLDebug::checkShaderCompilation(vertex);
        
        GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        GLDebug::checkShaderCompilation(fragment);

        // shader Program
        program = glCreateProgram();
        glAttachShader(program, vertex);
        glAttachShader(program, fragment);
        glLinkProgram(program);
        GLDebug::checkProgramLinking(program);
        
        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    void use()
    {
        glUseProgram(program);
    }

    void setBool(const std::string &name, bool value) const
    {
        glUniform1i(glGetUniformLocation(program, name.c_str()), (int)value);
    }

    void setInt(const std::string &name, int value) const
    {
        glUniform1i(glGetUniformLocation(program, name.c_str()), value);
    }
    
    void setFloat(const std::string &name, float value) const
    {
        glUniform1f(glGetUniformLocation(program, name.c_str()), value);
    }
    
    void setVec2(const char *name, const glm::vec2 &value)
    {
        glUniform2f(glGetUniformLocation(program, name), value.x, value.y);
    }
    
    void setVec3(const char *name, const glm::vec3 &value)
    {
        glUniform3f(glGetUniformLocation(program, name), value.x, value.y, value.z);
    }
    
    void setMat4(const std::string &name, glm::mat4 value) const
    {
        glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
    }
};

#endif /* GLShader_h */
