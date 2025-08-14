//
//  GLDebug.h
//  GameEngine
//
//  Created by John Saba on 8/18/24.
//

#ifndef GLDebug_h
#define GLDebug_h

#include <glad/glad.h>
#include <SDL2/SDL.h>

struct GLDebug 
{
    static void checkShaderCompilation(GLuint shader)
    {
        if(!glIsShader(shader))
        {
            SDL_Log("Name %d is not a shader\n", shader);
            return;
        }
        
        // Check for compile errors
        int success = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        
        if (!success)
        {
            SDL_Log("Failed to compile shader\n");
        }
        
        // Get log: will be > 0 with errors
        int infoLogLength = 0;
        int maxLength = infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
        
        char* infoLog = new char[maxLength];
        glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
        
        if(infoLogLength > 0)
        {
            SDL_Log("%s\n", infoLog);
        }
        
        delete[] infoLog;
    }
    
    static void checkProgramLinking(GLuint program)
    {
        if(!glIsProgram(program))
        {
            SDL_Log("Name %d is not a program\n", program);
        }
        
        // Check for link errors
        int success = 0;
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        
        if (!success)
        {
            SDL_Log("Failed to link program\n");
        }
        
        // Get log: will be > 0 with errors
        int infoLogLength = 0;
        int maxLength = infoLogLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
        
        char* infoLog = new char[maxLength];
        glGetProgramInfoLog(program, maxLength, &infoLogLength, infoLog);
        
        if(infoLogLength > 0)
        {
            SDL_Log("%s\n", infoLog);
        }
        
        delete[] infoLog;
    }
};

#endif /* GLDebug_h */
