/*!
** Description of a Texture Atlas for rendering fonts
**    
** @since 2013-09-16
*/
#ifndef TEXTUREATLAS_H__
#define TEXTUREATLAS_H__
 
#include <string>
#include "../Util.h"
#include "../GL/Texture2D.h"
#include "../Math/Vector2.h"

namespace APP
{
    class TextureAtlas
    {
    public:
        TextureAtlas(const std::string& font, unsigned int fontSize);
        ~TextureAtlas();

        
        int GetHeight() const {return height_;}
        int GetWidth() const {return width_;}
        
        int GetAtlasOffX(char c) const {return atlasOffX_[static_cast<int>(c)];}
        int GetBitmapWidth(char c) const {return bitmapWidth_[static_cast<int>(c)];}
        const Math::Vector2I& GetAdvance(char c) const {return advances_[static_cast<int>(c)];}
        const Math::Vector2I& GetBearing(char c) const {return bearings_[static_cast<int>(c)];}

        /*!
        ** Binds the texture atlas to a texture unit.
        */
        void Bind(int i) const;


        void SaveToBMP(const std::string& filename) const;



    public:
        DECL_DEFAULTS(TextureAtlas)

        GL::Tex2DR8FR8UI* atlas_;

        int width_;
        int height_;
        
        int bitmapWidth_[128];
        int atlasOffX_[128];
        Math::Vector2I advances_[128];
        Math::Vector2I bearings_[128];

    };
}
 
#endif /* end of include guard: TEXTUREATLAS_H__ */