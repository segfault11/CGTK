#include <sstream>
#include "GLUE.h"
#include "../Error/Error.h"


void GLUE::ProgramAttachShaderFromSource(
    GLuint program, 
    GLenum type, 
    const char* source
)
{
    // create the shader
    GLuint shader = glCreateShader(type);

    if (shader == 0)
    {
        CGTK_REPORT("Could not create shader.", CGTK_GL_ERROR);
        return;
    }

    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    // check if shader compiled correctly, delete it if not
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
        
        GLchar *infoLog = new GLchar[infoLogLength + 1];
        glGetShaderInfoLog(shader, infoLogLength, NULL, infoLog);
        
        std::stringstream message;
        message << "Could not compile shader. "  << std::endl;
        message << infoLog << std::endl;

        delete[] infoLog;        
        
        glDeleteShader(shader);

        CGTK_REPORT(message.str().c_str(), CGTK_GL_ERROR);
        return;
    }    

    glAttachShader(program, shader);
}

void GLUE::ProgramLink(GLuint program)
{
    glLinkProgram(program);

    int status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);

    if (status != GL_TRUE)
    {
        char* log;
        GLint logLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
        log = new char[logLength + 1];
        glGetProgramInfoLog(program, logLength, NULL, log);
        CGTK_REPORT(log, CGTK_GL_ERROR);
        delete[] log;
    }
    
    // detach and delete shaders 
    GLint numShaders;
    glGetProgramiv(program, GL_ATTACHED_SHADERS, &numShaders);
    GLuint* shaders = new GLuint[numShaders];
    glGetAttachedShaders(program, numShaders, NULL, shaders);

    for (int i = 0; i < numShaders; ++i)
    {
        glDetachShader(program, shaders[i]);  
        glDeleteShader(shaders[i]);
    }
    
    delete[] shaders;
}