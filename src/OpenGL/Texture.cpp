//------------------------------------------------------------------------------
#include "Texture.h"
#include <cstring>
#include "../Error/Error.h"
#include "../External/SOIL/SOIL.h"
#include "../Util.h"
#include <iostream>
//------------------------------------------------------------------------------
GLuint CGKOpenGLTexture2DCreateFromFile(const char *filename)
{
    if (filename == NULL)                                                        // TODO: Bind the previous bound tex 
    {                                                                            //       after tex is created.
        CGK_REPORT("Invalid file name", CGK_INVALID_FILE);
        return 0;
    }

    // load the image
    int width, height, channels;

    unsigned char* data = SOIL_load_image(
        filename,
        &width, &height, &channels,
        SOIL_LOAD_AUTO
    );

    if (data == NULL)
    {
        CGK_REPORT("Image could not be loaded", CGK_INVALID_FILE);
        return 0;
    }

    // create the texture
    GLuint handle;
    glGenTextures(1, &handle);

    if (handle == 0)
    {
        CGK_REPORT("Texture could not be created.", CGK_INVALID_FILE);
        return 0;
    }

    glBindTexture(GL_TEXTURE_2D, handle);

    if (channels == 3)
    {
        glTexImage2D(
            GL_TEXTURE_2D, 0, GL_RGB, 
            width, height, 0, 
            GL_RGB, GL_UNSIGNED_BYTE, data
        );
        
    }
    else if (channels == 4)
    {
        glTexImage2D(
            GL_TEXTURE_2D, 0, GL_RGBA, 
            width, height, 0, 
            GL_RGBA, GL_UNSIGNED_BYTE, data
        );
    }
    else
    {
        CGK_REPORT("Number of channels not supported", CGK_INVALID_FILE);
        glDeleteTextures(1, &handle);
        return 0;
    }
    
    // clean up
    SOIL_free_image_data(data);

    CGK_ASSERT(GL_NO_ERROR == glGetError())

    if (GL_NO_ERROR != glGetError())
    {
        glDeleteTextures(1, &handle);
        return 0;
    }

    // give the tex a default config
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    return handle;
}
//------------------------------------------------------------------------------
void CGKOpenGLTexture2DSaveAsBMP(const char* filename, GLuint handle)
{
    glGetError();

    // check for correct file name and handle
    if (filename == NULL)
    {
        CGK_REPORT("Invalid file name", CGK_INVALID_FILE);
        return;
    }

    const char* subptr = std::strstr(filename, ".bmp");

    if (subptr == NULL)
    {
        CGK_REPORT("Invalid filename", CGK_INVALID_FILE);
        return;
    }

    int pos = subptr - filename;
    int numChars = std::strlen(filename);

    if (numChars - pos != 4)
    {
        CGK_REPORT("Invalid filename", CGK_INVALID_FILE);
        return;
    }

    if (handle == 0)
    {
        CGK_REPORT("Invalid texure handle", CGK_INVALID_TEXTURE);
        return;
    }

    // get texture information and image data
    glBindTexture(GL_TEXTURE_2D, handle);
    GLint width, height, channels, internalFormat;

    glGetTexLevelParameteriv(  
        GL_TEXTURE_2D,
        0,
        GL_TEXTURE_WIDTH,
        &width
    );

    glGetTexLevelParameteriv(  
        GL_TEXTURE_2D,
        0,
        GL_TEXTURE_HEIGHT,
        &height
    );

    glGetTexLevelParameteriv(  
        GL_TEXTURE_2D,
        0,
        GL_TEXTURE_INTERNAL_FORMAT,
        &internalFormat
    );

    unsigned char* data = NULL;

    switch (internalFormat)
    {   
        case GL_RED:
        case GL_R8:
            channels = 1;
            data = new unsigned char[width*height*channels];
            glGetTexImage(GL_TEXTURE_2D, 0, GL_RED, GL_UNSIGNED_BYTE, data);
            break;
        
        case GL_RGB:
        case GL_RGB8:
            channels = 3;
            data = new unsigned char[width*height*channels];
            glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            break;

        case GL_RGBA:
        case GL_RGBA8:
            channels = 4;
            data = new unsigned char[width*height*channels];
            glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            break;

        default:
            CGK_REPORT(
                "Internal format of texture not supported.", 
                CGK_INVALID_TEXTURE
            )
            std::cout << internalFormat << std::endl;
            return;
    }
   
    // save the result
    int result = SOIL_save_image(
        filename,
        SOIL_SAVE_TYPE_BMP,
        width, height, channels,
        data
    );  

    if (result == 0)
    {
        CGK_REPORT("Failed saving the texture", CGK_UNKNOWN_ERROR)
    }  

    CGK_ASSERT(GL_NO_ERROR == glGetError())

    // clean up
    CGK_DELETE(data)
}
//------------------------------------------------------------------------------