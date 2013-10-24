#include "BufferObject.h"
#include "../Error/Error.h"
#include <iostream>

GL::BufferObject::BufferObject(GLenum target, GLsizeiptr size, GLenum usage)
: buffer_(0), target_(target), usage_(usage)
{
    glGetError();
    glGenBuffers(1, &buffer_);
    glBindBuffer(target, buffer_);
    glBufferData(target, size, NULL, usage);

    GLenum error = glGetError();
    if (GL_NO_ERROR != error)
    {
        CGTK_REPORT((const char*)gluErrorString(error), CGTK_GL_ERROR);
    }
}

GL::BufferObject::~BufferObject()
{
    glDeleteBuffers(1, &buffer_);
}

void GL::BufferObject::SetData(    
    GLsizeiptr size, 
    const void* data
)
{
    this->Bind();
    glGetError();
    glBufferSubData(target_, 0, size, data);
    
    GLenum error = glGetError();
    if (GL_NO_ERROR != error)
    {
        CGTK_REPORT((const char*)gluErrorString(error), CGTK_GL_ERROR);
    }    
}

void GL::BufferObject::Bind()
{
    glBindBuffer(target_, buffer_);
}

void GL::BufferObject::Unbind()
{
    glBindBuffer(target_, 0);
}

