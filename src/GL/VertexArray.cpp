#include "VertexArray.h"
#include <iostream>
//------------------------------------------------------------------------------
GL::VertexArray::VertexArray()
{
    glGenVertexArrays(1, &vertexArray_);
}
//------------------------------------------------------------------------------
GL::VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &vertexArray_);
}
//------------------------------------------------------------------------------
void GL::VertexArray::Bind() const
{
    glBindVertexArray(vertexArray_);
}
//------------------------------------------------------------------------------
void GL::VertexArray::Unbind() const
{
    glBindVertexArray(0);
}
//------------------------------------------------------------------------------
void GL::VertexArray::SetAttribute(
    BufferObject* object, 
    GLuint index, 
    GLint size, 
    GLenum type, 
    GLboolean normalized, 
    GLsizei stride, 
    const void* offset
)
{
    this->Bind(); 
    object->Bind();
    glVertexAttribPointer(index, size, type, normalized, stride, offset); 
    glEnableVertexAttribArray(index);   
    object->Unbind();
    this->Unbind();
}
//------------------------------------------------------------------------------