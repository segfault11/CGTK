//------------------------------------------------------------------------------
#include <sstream>
#include "Program.h"
#include "../Error/Error.h"
#include <iostream>
#include <fstream>
#include <streambuf>
#include <string>
#include <cerrno>
//------------------------------------------------------------------------------
bool getFileContents(std::string& contents, const char *filename)
{
    std::ifstream in(filename, std::ios::in);
    
    if (!in.is_open())
    {
        return false;
    }

    in.seekg(0, std::ios::end);
    contents.reserve(in.tellg());
    in.seekg(0, std::ios::beg);

    contents.assign(
        std::istreambuf_iterator<char>(in), 
        std::istreambuf_iterator<char>()
    );

    in.close();

    return true;
}
//------------------------------------------------------------------------------
void CGKOpenGLProgramAttachShaderFromSource(
    GLuint program, 
    GLenum type, 
    const char* source
)
{
    // create the shader
    GLuint shader = glCreateShader(type);

    if (shader == 0)
    {
        CGK_REPORT("Could not create shader.", CGK_GL_ERROR);
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

        CGK_REPORT(message.str().c_str(), CGK_GL_ERROR);
        return;
    }    

    glAttachShader(program, shader);
}
//------------------------------------------------------------------------------
void CGKOpenGLProgramAttachShaderFromFile(
    GLuint program, 
    GLenum type, 
    const char *filename
)
{
    std::string contents;

    if (!getFileContents(contents, filename))
    {
        CGK_REPORT("Could not open file", CGK_INVALID_FILE);
        return;
    }

    CGKOpenGLProgramAttachShaderFromSource(
        program, 
        type, 
        contents.c_str()
    );
}
//------------------------------------------------------------------------------
void CGKOpenGLProgramLink(GLuint program)
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
        CGK_REPORT(log, CGK_GL_ERROR);
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
//------------------------------------------------------------------------------
void CGKOpenGLProgramUniformMatrix4F(
    GLuint program,
    const char* name, 
    const GLfloat* value, 
    GLboolean transpose
)
{
    GLint loc = glGetUniformLocation(program, name);
    CGK_ASSERT(loc != -1)
    glUniformMatrix4fv(loc, 1, transpose, value);
}
//------------------------------------------------------------------------------
void CGKOpenGLProgramUniform1I(
    GLuint program,
    const char* name, 
    GLint value
)
{
    GLint loc = glGetUniformLocation(program, name);
    CGK_ASSERT(loc != -1)
    glUniform1i(loc, value);
}
//------------------------------------------------------------------------------