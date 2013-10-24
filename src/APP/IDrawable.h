#ifndef IDRAWABLE_H__
#define IDRAWABLE_H__

#include "IObject.h"

namespace APP
{
    class IDrawable : public IObject
    {
    public:
        IDrawable() {};
        ~IDrawable() {};

        virtual void Draw() = 0;
    };    
}
 
#endif /* end of include guard: IDRAWABLE_H__ */
