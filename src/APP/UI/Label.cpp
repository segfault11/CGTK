#include <cstdlib>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "Label.h"
#include "../Application.h"
#include "../../GLA/GLA.h"
#include "../../Error/Error.h"
#include "../../Util.h"
#include "../../Math/Vector2.h"


// [FontPtr]'s DEFINITION //////////////////////////////////////////////////////

struct APP::UI::Font
{
    // INTERNAL REPRESENTATION OF A FONT

    GLuint TexAtlas; // handle to the gl texture atlas
    GLint TexWidth;
    GLint TexHeight;

    // Glyph info
    int BitmapWidth[128];          
    int AtlasOffX[128];
    Math::Vector2I Advances[128];
    Math::Vector2I Bearings[128];
};

APP::UI::FontPtr APP::UI::FontCreate(const char* filename, unsigned int size)
{
    // check if we have an OpenGL context
    if (!APP::IsInitialized())
    {
        CGTK_REPORT("Application was not initialized", CGTK_UNKNOWN_ERROR);
        return NULL;
    }

    FT_Library library;

    // load the library
    FT_Error err = FT_Init_FreeType(&library);

    CGTK_ASSERT(err == 0)

    FT_Face face;

    // load the font (face)
    err = FT_New_Face(
            library,
            filename,
            0,
            &face 
        );

    if (!(err == 0))
    {
        CGTK_REPORT("Application was not initialized", CGTK_UNKNOWN_ERROR);
        return NULL;
    }

    FT_Set_Pixel_Sizes(face, 0, size);    

    FT_GlyphSlot g = face->glyph;
    int atlasWidth = 0;
    int atlasHeight = 0;

    // compute the dimensions of the atlas
    for (unsigned int i = 32; i < 128; i++) 
    {
        if(FT_Load_Char(face, i, FT_LOAD_RENDER)) 
        {
            CGTK_REPORT("Loading character %c failed!", CGTK_INVALID_FILE)
            continue;
        }

        atlasWidth += g->bitmap.width;
        atlasHeight = std::max(atlasHeight, g->bitmap.rows);
    }

    unsigned char* atlas = new unsigned char[atlasWidth*atlasHeight];
    
    for (unsigned int i = 0; i < atlasHeight*atlasWidth; i++)
    {
        atlas[i] = 0;
    }

    // create a font struct    
    Font* font = new Font;

    font->TexWidth = atlasWidth;
    font->TexHeight = atlasHeight;

    int marker = 0;

    // fill the atlas and the [font] with information about each character. 
    for (unsigned int i = 32; i < 128; i++) 
    {
        if(FT_Load_Char(face, i, FT_LOAD_RENDER)) 
        {
            continue;
        }
        
        int w = g->bitmap.width;
        int h = g->bitmap.rows;
        
        unsigned char* buffer = g->bitmap.buffer;
        
        // copy character to atlas
        for (unsigned int v = 0; v < h; v++)
        {
            for (unsigned int u = 0; u < w; u++)
            {
                int y = atlasHeight - 1 - v;
                int x = marker + u;
                atlas[y*atlasWidth + x] = buffer[v*w + u];
            }
        }
        // save character info
        font->BitmapWidth[i]  = w;
        font->AtlasOffX[i] = marker;
        font->Advances[i] = Math::Vector2I(g->advance.x >> 6, g->advance.y >> 6);
        font->Bearings[i] = Math::Vector2I(g->bitmap_left, g->bitmap_top);

        // increase marker
        marker += w;
    }

    // create and configure the texture atlas
    glGenTextures(1, &font->TexAtlas);
    glBindTexture(GL_TEXTURE_2D, font->TexAtlas);
    glTexImage2D(
        GL_TEXTURE_2D, 0, GL_R8, atlasWidth, atlasHeight, 
        0, GL_RED, GL_UNSIGNED_BYTE, atlas
    );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_PACK_ALIGNMENT, 4); // for saving the image as bmp.

    CGTK_ASSERT(GL_NO_ERROR == glGetError())

    GLA::Texture2DSaveAsBMP("atlas.bmp", font->TexAtlas);

    // clean up
    delete[] atlas;
    FT_Done_FreeType(library);

    return font;
}

void APP::UI::FontDestroy(FontPtr *font)
{
    glDeleteTextures(1, &(*font)->TexAtlas);
    CGTK_DELETE(*font);
    *font = NULL;
}



