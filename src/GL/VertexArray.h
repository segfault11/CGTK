/*!
** Wrapper of an OpenGL Vertex Array Object.
**  
** @since 2013-08-20
*/
#ifndef VERTEXARRAYOBJECT_H__
#define VERTEXARRAYOBJECT_H__

//#include "glcorearb.h"
#include <GL/glew.h>
#include "BufferObject.h"

namespace GL
{
    class VertexArray
    {
    public:
        VertexArray();
        ~VertexArray();

        operator GLuint(){return vertexArray_;};

        
        void SetAttribute(
            BufferObject* object, 
            GLuint index, 
            GLint size, 
            GLenum type, 
            GLboolean normalized, 
            GLsizei stride, 
            const void* offset
        );
        void Bind() const;
        void Unbind() const;

    private:
        VertexArray(const VertexArray& orig);
        VertexArray& operator=(const VertexArray& orig);


        GLuint vertexArray_;
    };
}
 
#endif /* end of include guard: VERTEXARRAYOBJECT_H__ */
