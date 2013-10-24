/*!
** Wrapper of an opengl shader.
**  
** @since 2013-08-19 
*/
#ifndef SHADER_H__
#define SHADER_H__

//#include "glcorearb.h"
#include <GL/glew.h>

namespace GL
{
    class Shader
    {
    public:
        Shader();
        Shader(const char* source, GLenum type);
        ~Shader();

        /*!
        ** Loads a shader from file.
        */
        void Load(const char* filename, GLenum type);



        operator GLuint() {return shader_;}; 

    private:
        GLuint shader_;

    };
}
#endif /* end of include guard: SHADER_H__ */
