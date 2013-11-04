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

    /*!
    ** Sets a uniform Mat4 variable identified by [name] in the glsl object.
    ** NOTE: THE GLSL OBJECT SHOULD BE BOUND BEFORE USING THIS FUNCTION.
    */
    void ProgramUniformMatrix4F(
        GLuint program,
        const char* name, 
        const GLfloat* value, 
        GLboolean transpose
    );

    /*!
    ** Sets a uniform int variable identified by [name] in the glsl object.
    ** NOTE: THE GLSL OBJECT SHOULD BE BOUND BEFORE USING THIS FUNCTION.
    */
    void ProgramUniform1I(
        GLuint program,
        const char* name, 
        GLint value
    );

}
 
#endif /* end of include guard: PROGRAM_H__ */