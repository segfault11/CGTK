#ifndef IEVENTHANDLER_H__
#define IEVENTHANDLER_H__

#include <SDL2/SDL.h>
#include "IObject.h"

namespace APP
{
    class IEventHandler : public IObject
    {
    public:
        IEventHandler() {};
        ~IEventHandler() {};

        virtual void OnEvent(const SDL_Event& Event);
        virtual void OnKeyDown(SDL_Keycode key);
        virtual void OnKeyUp(SDL_Keycode key);
        
    };    
}
 
#endif /* end of include guard: IEVENTHANDLER_H__ */