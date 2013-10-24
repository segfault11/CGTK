#include "Program.h"
#include <stdexcept>
#include <fstream>
#include <iostream>
#include "../Error/Error.h"

GL::Program::Program()
: compiled_(false), program_(0), vertexShader_(NULL), fragmentShader_(NULL)
{
     program_ = glCreateProgram();

     if (program_ == 0)
     {
        throw std::runtime_error("Could not create program.");
     }
}

GL::Program::~Program()
{
    if (!program_)
    {
        return;
    }

    glDeleteProgram(program_);
    delete vertexShader_;
    delete fragmentShader_;
}

void GL::Program::AttachShader(const char* filename, GLenum type)
{
    if (compiled_)
    {
        CGTK_REPORT("Program is already compiled.", CGTK_GL_ERROR);
        return;
    }

    Shader* shader = new Shader();
    shader->Load(filename, type);

    // check if a shader was already attached
    switch (type)
    {
        case GL_VERTEX_SHADER:
            
            if (vertexShader_)
            {
                glDetachShader(program_, *vertexShader_);
                delete vertexShader_;
                CGTK_REPORT("Vertex shader was replaced.", CGTK_GL_ERROR)
            }

            vertexShader_ = shader;
        
            break;

        case GL_FRAGMENT_SHADER:

            if (fragmentShader_)
            {
                glDetachShader(program_, *fragmentShader_);
                delete fragmentShader_;
                CGTK_REPORT("Vertex shader was replaced.", CGTK_GL_ERROR)
            }

            fragmentShader_ = shader;
        
            break;
    }

    glAttachShader(program_, *shader);
}

void GL::Program::AttachShaderFromSource(const char* source, GLenum type)
{
    if (compiled_)
    {
        CGTK_REPORT("Program is already compiled.", CGTK_GL_ERROR);
        return;
    }

    Shader* shader = new Shader(source, type);

    // check if a shader was already attached
    switch (type)
    {
        case GL_VERTEX_SHADER:
            
            if (vertexShader_)
            {
                glDetachShader(program_, *vertexShader_);
                delete vertexShader_;
                CGTK_REPORT("Vertex shader was replaced.", CGTK_GL_ERROR)
            }

            vertexShader_ = shader;
        
            break;

        case GL_FRAGMENT_SHADER:

            if (fragmentShader_)
            {
                glDetachShader(program_, *fragmentShader_);
                delete fragmentShader_;
                CGTK_REPORT("Vertex shader was replaced.", CGTK_GL_ERROR)
            }

            fragmentShader_ = shader;
        
            break;
    }

    glAttachShader(program_, *shader);
}

void GL::Program::BindAttribLocation(GLuint index, const char* name)
{
    if (compiled_)
    {
        CGTK_REPORT("Program was already compiled.", CGTK_GL_ERROR)
        return;
    }

    glBindAttribLocation(program_, index, name);
}

void GL::Program::BindFragDataLocation(GLuint colorNumber, const char* name)
{
    if (compiled_)
    {
        CGTK_REPORT("Program was already compiled.", CGTK_GL_ERROR)
        return;
    }

    glBindFragDataLocation(program_, colorNumber, name);
}

void GL::Program::Compile()
{
    if (compiled_)
    {
        CGTK_REPORT("Program is already compiled.", CGTK_GL_ERROR);
        return;
    }

    if (vertexShader_ == NULL || fragmentShader_ == NULL)
    {
        CGTK_REPORT("Could not compile program.", CGTK_GL_ERROR);
    }

    glLinkProgram(program_);

    int status;
    glGetProgramiv(program_, GL_LINK_STATUS, &status);

    if (status != GL_TRUE)
    {
        char* log;
        GLint logLength;
        glGetProgramiv(program_, GL_INFO_LOG_LENGTH, &logLength);
        log = new char[logLength + 1];
        glGetProgramInfoLog(program_, logLength, NULL, log);
        CGTK_REPORT(log, CGTK_GL_ERROR);
        delete[] log;
    }

    glDetachShader(program_, *vertexShader_);
    glDetachShader(program_, *fragmentShader_);
    
    compiled_ = true;
}

void GL::Program::Bind() const
{
    CGTK_ASSERT(compiled_)

    glUseProgram(program_);
}

void GL::Program::Unbind() const
{
    CGTK_ASSERT(compiled_)

    glUseProgram(0);
}

void GL::Program::SetMat4(const char* name, const GLfloat* data)
{
    CGTK_ASSERT(compiled_)
    
    this->Bind();
    GLint loc = glGetUniformLocation(program_, name);

    CGTK_ASSERT(loc != -1)

    glUniformMatrix4fv(loc, 1, GL_FALSE, data);
}

void GL::Program::SetInt(const char* name, GLint i)
{
    CGTK_ASSERT(compiled_)
    
    this->Bind();
    GLint loc = glGetUniformLocation(program_, name);

    CGTK_ASSERT(loc != -1)

    glUniform1i(loc, i);
}

void GL::Program::SetIVec2(const char* name, const GLint* ivec)
{
    CGTK_ASSERT(compiled_)
    
    this->Bind();
    GLint loc = glGetUniformLocation(program_, name);

    CGTK_ASSERT(loc != -1)

    glUniform2i(loc, ivec[0], ivec[1]);    
}

void GL::Program::SetVec3(const char* name, const GLfloat* vec)
{
    CGTK_ASSERT(compiled_)
    
    this->Bind();
    GLint loc = glGetUniformLocation(program_, name);

    CGTK_ASSERT(loc != -1)

    glUniform3f(loc, vec[0], vec[1], vec[2]);    
}

