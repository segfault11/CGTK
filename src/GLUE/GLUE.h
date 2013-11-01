/*!
** Declaration of various GL helper functions.
**    
** @since 2013-09-10
*/
/**
    TODOS:
        Texture2DCreateFromFile:
        - allow user to specify internal format and other params of the tex

        Texture2DSaveAsBMP:
        - complete the check to figure out the channels of the texture
*/
#include <GL/GLEW.h>

namespace GLUE
{
    /*!
    ** Creates an OpenGL 2D texture from an image file. The caller is 
    ** responsible to release the texture.
    **
    ** @param filename Filename of the image to be loaded.
    ** @return Handle to the texture if succeeded. Otherwise 0.
    */
    GLuint Texture2DCreateFromFile(const char* filename);

    /*!
    ** Saves the texture's image data as an bmp file. Fails if [filename]
    ** does not end with ".bmp".
    */
    void Texture2DSaveAsBMP(const char* filename, GLuint handle);

    /*!
    ** Attaches a shader to the program. The shader is defined by the c string
    ** [source] and is of type [type].
    */
    void ProgramAttachShaderFromSource(
        GLuint program, GLenum type, const char* source
    );

    /*!
    ** Links the program and detaches and deletes its attached shaders
    */
    void ProgramLink(GLuint program);
}