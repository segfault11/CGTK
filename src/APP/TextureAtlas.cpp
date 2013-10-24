#include "TextureAtlas.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include <iostream>
#include <cmath>
#include "../GL/Program.h"
#include "Application.h"

APP::TextureAtlas::TextureAtlas(const std::string& font, unsigned int fontSize)
{
    // INIT FREETYPE AND CREATE FONT ATLAS

    // check if we have and OpenGL context
    CGTK_ASSERT(APP::IsInitialized())

    FT_Library library;

    // load the library
    FT_Error err = FT_Init_FreeType(&library);

    CGTK_ASSERT(err == 0)

    FT_Face face;

    // load the font (face)
    err = FT_New_Face(
            library,
            font.c_str(),
            0,
            &face 
        );

    CGTK_ASSERT(err == 0)

    FT_Set_Pixel_Sizes(face, 0, fontSize);    

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

    int marker = 0;

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
        bitmapWidth_[i]  = w;
        atlasOffX_[i] = marker;
        advances_[i] = Math::Vector2I(g->advance.x >> 6, g->advance.y >> 6);
        bearings_[i] = Math::Vector2I(g->bitmap_left, g->bitmap_top);

        // increase marker
        marker += w;
    }


    // initialize member
    atlas_ = new GL::Tex2DR8FR8UI(
            atlasWidth, 
            atlasHeight, 
            static_cast<void*>(atlas)
        );   

    width_ = atlasWidth;
    height_ = atlasHeight;


    // clean up
    delete[] atlas;
    FT_Done_FreeType(library);
}

APP::TextureAtlas::~TextureAtlas()
{
    delete atlas_;
}

void APP::TextureAtlas::Bind(int i) const
{
    atlas_->Bind(i);
}