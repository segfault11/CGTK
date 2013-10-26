#include "GLA.h"
#include <cstring>
#include "../Error/Error.h"
#include "../External/SOIL/SOIL.h"
#include "../Util.h"
#include <iostream>

// PUBLIC DEFININTIONS /////////////////////////////////////////////////////////


GLuint GLA::Texture2DCreateFromFile(const char *filename)
{
    if (filename == NULL)
    {
        CGTK_REPORT("Invalid file name", CGTK_INVALID_FILE);
        return 0;
    }

    // load the image
    int width, height, channels;

    std::cout << "start loading image" << std::endl;

    unsigned char* data = SOIL_load_image(
        filename,
        &width, &height, &channels,
        SOIL_LOAD_AUTO
    );
    
    std::cout << "loaded succesful" << " width " << width << "height " << height << "channels " << channels <<  std::endl;

    if (data == NULL)
    {
        CGTK_REPORT("Image could not be loaded", CGTK_INVALID_FILE);
        return 0;
    }

    // create the texture
    GLuint handle;
    glGenTextures(1, &handle);

    if (handle == 0)
    {
        return 0;
    }
    std::cout << "GL_ERROR" << std::endl;

    glBindTexture(GL_TEXTURE_2D, handle);

    std::cout << "GL_ERROR" << std::endl;

    for (int i = 0; i < width*height+5; ++i)
    {
        //std::cout << "bla " << int(data[i]) << std::endl;
    }

    if (channels == 3)
    {
        glTexImage2D(
            GL_TEXTURE_2D, 0, GL_RGB, 
            width, height, 0, 
            GL_RGB, GL_UNSIGNED_BYTE, data
        );
        std::cout << "GL_ERROR" << std::endl;

    }
    else if (channels == 4)
    {
        glTexImage2D(
            GL_TEXTURE_2D, 0, GL_RGBA, 
            width, height, 0, 
            GL_RGBA, GL_UNSIGNED_BYTE, data
        );
        std::cout << "GL_ERROR" << std::endl;

    }
    else
    {
        CGTK_REPORT("Number of channels not supported", CGTK_INVALID_FILE);
        glDeleteTextures(1, &handle);
        return 0;
    }
    
    // clean up
    SOIL_free_image_data(data);

    return handle;
}

void GLA::Texture2DSaveAsBMP(const char* filename, GLuint handle)
{
    if (filename == NULL)
    {
        CGTK_REPORT("Invalid file name", CGTK_INVALID_FILE);
        return;
    }

    // check for correct file name and handle
    const char* subptr = std::strstr(filename, ".bmp");

    if (subptr == NULL)
    {
        CGTK_REPORT("Invalid filename", CGTK_INVALID_FILE);
        return;
    }

    int pos = subptr - filename;
    int numChars = std::strlen(filename);

    if (numChars - pos != 4)
    {
        CGTK_REPORT("Invalid filename", CGTK_INVALID_FILE);
        return;
    }

    if (handle == 0)
    {
        CGTK_REPORT("Invalid texure handle", CGTK_INVALID_TEXTURE);
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
            CGTK_REPORT(
                "Internal format of texture not supported.", 
                CGTK_INVALID_TEXTURE
            )
            std::cout << internalFormat << std::endl;
            std::cout << GL_RGB << std::endl;
            std::cout << GL_RGBA << std::endl;
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
        CGTK_REPORT("Failed saving the texture", CGTK_UNKNOWN_ERROR)
    }  

    // clean up
    CGTK_DELETE(data)
}