/*!
** Implementation of an GLSL Object
**  
** @since 2013-08-16
*/
#ifndef PROGRAM_H__
#define PROGRAM_H__

#include "Shader.h"
#include <GL/glew.h> 
//#include "glcorearb.h"

namespace GL
{
    class Program
    {
    public:
        Program();
        ~Program();

        void AttachShader(const char* filename, GLenum type);
        void AttachShaderFromSource(const char* source, GLenum type);
        void BindAttribLocation(GLuint index, const char* name);
        void BindFragDataLocation(GLuint colorNumber, const char* name);

        /*
        **  Setter for programm variables. 
        */
        void SetMat4(const char* name, const GLfloat* data);
        void SetInt(const char* name, GLint i);
        void SetIVec2(const char* name, const GLint* ivec);
        void SetVec3(const char* name, const GLfloat* vec);

        void Compile();
        void Bind() const;
        void Unbind() const;

    private:
        bool compiled_;
        GLuint program_;
        Shader* vertexShader_;
        Shader* fragmentShader_;
    };
}
 
#endif /* end of include guard: PROGRAM_H__ */
