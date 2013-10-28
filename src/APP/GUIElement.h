/*!
** Description of a GUI Element
**    
** @since 2013-09-17
*/
#ifndef GUIRENDERER_H__
#define GUIRENDERER_H__

#include "../Math/Vector3.h"
#include "IDrawable.h"

namespace APP 
{
    class GUIElement : public IDrawable
    {
    public:
        GUIElement(
            const std::string& text, 
            const Math::Vector2I& pos,
            const TextureAtlas& atlas
        );
        ~GUIElement();

        void SetText(const std::string& text);

        virtual void Draw();

    private:
        DECL_DEFAULTS(GUIElement)  
    };
    
}
 
#endif /* end of include guard: GUIELEMENT_H__ */