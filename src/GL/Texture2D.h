/*!
** Description of an OpenGL 2D texture
**    
** @since 2013-09-15 
*/
#ifndef TEXTURE2D_H__
#define TEXTURE2D_H__

#include "GL/glew.h" 
#include "../Error/Error.h"
#include <string>
#include <iostream>

namespace GL
{
    /*!
    ** Convenience wrapper for two dimensional OpenGL textures
    */
    template<GLint INTERNAL, GLenum FORMAT, GLenum TYPE> 
    class Texture2D
    {
    public:
        Texture2D(GLsizei width, GLsizei height, const GLvoid* data);
        ~Texture2D();
    
        GLsizei GetWidth() const {return width_;}
        GLsizei GetHeight() const {return height_;}

        /*!
        ** Binds the texture to a texture unit specified by [unit].
        */
        void Bind(int unit) const;

        GLuint GetHandle() const {return texture_;}
    

    private:
        Texture2D();
        Texture2D(const Texture2D& orig);
        Texture2D operator=(const Texture2D& orig);

        GLsizei width_;
        GLsizei height_;
        GLuint texture_;
    };

    #include "Texture2D.inl"
    
    typedef Texture2D<GL_R8, GL_RED, GL_UNSIGNED_BYTE> Tex2DR8FR8UI;
}
 
#endif /* end of include guard: TEXTURE2D_H__ */