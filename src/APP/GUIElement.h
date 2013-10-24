/*!
** Description of a GUI Element
**    
** @since 2013-09-17
*/
#ifndef GUIRENDERER_H__
#define GUIRENDERER_H__

#include "../GL/Program.h"
#include "../GL/VertexArray.h"
#include "../GL/BufferObject.h"
#include "../Math/Vector3.h"
#include "TextureAtlas.h" 
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
        
        void refillBufferObject();
        void createVertexArray();

        GL::VertexArray* vertexArray_;
        GL::BufferObject* bufferObject_;

        const TextureAtlas* atlas_;
        GL::Program program_;

        std::string text_;
        Math::Vector2I position_; 
        Math::Vector3F textColor_;        
    };
    
}
 
#endif /* end of include guard: GUIELEMENT_H__ */