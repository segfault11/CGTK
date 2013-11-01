#ifndef PROGRAM_H__
#define PROGRAM_H__
 
#include <GL/GLEW.h>

namespace GLUE
{
    /*!
    ** Attaches a shader to the program. The shader is defined by the c string
    ** [source] and is of type [type].
    */
    void ProgramAttachShaderFromSource(
        GLuint program, GLenum type, const char* source
    );

    /*!
    ** Attaches a shader to the program. The shader is defined by the file 
    ** referenced by [filename] and is of type [type].
    */
    void ProgramAttachShaderFromFile(
        GLuint program, GLenum type, const char* filename
    );

    /*!
    ** Links the program and detaches and deletes its attached shaders
    */
    void ProgramLink(GLuint program);
}
 
#endif /* end of include guard: PROGRAM_H__ */