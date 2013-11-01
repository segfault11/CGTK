#ifndef LABEL_H__
#define LABEL_H__

#include <string>
#include "../IDrawable.h"
#include "../../Math/Vector3.h"
#include "../../Math/Vector2.h"

namespace APP
{
    namespace UI
    {
        /*!
        ** Defines a pointer to a font.
        */
        struct Font;
        typedef const Font* FontPtr;
    
        /*!
        ** Creates a font. Takes the filename and the size of the font as
        ** arguments. 
        **
        ** @return A pointer to the font if succeeded, otherwise NULL.
        */
        FontPtr FontCreate(const char* name, unsigned int size);
        
        /*!
        ** Destroys a font.                                                                                                                                                             
        */
        void FontDestroy(FontPtr* font);

        class Label : public APP::IDrawable
        {
        public:
            
            Label(
                const Math::Vector2I& pos,
                const std::string& text, 
                FontPtr font, 
                const Math::Vector3F& fontCol, 
                const Math::Vector3F& bgCol
            );
            ~Label();

        private:
            class RealLabel;
            RealLabel* label;
        };
    }
}
 
#endif /* end of include guard: LABEL_H__ */