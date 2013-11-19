#include "IEventHandler.h"
#include <iostream>
//------------------------------------------------------------------------------
void APP::IEventHandler::OnEvent(const SDL_Event& event)
{
    switch(event.type) 
    {
        case SDL_KEYDOWN: 

            if (event.key.repeat == 1)
            {
                return;
            }

            OnKeyDown(event.key.keysym.sym);
            break;
        
        case SDL_KEYUP: 
            OnKeyUp(event.key.keysym.sym);
            break;
    }   
}
//------------------------------------------------------------------------------
void APP::IEventHandler::OnKeyDown(SDL_Keycode key)
{

}
//------------------------------------------------------------------------------
void APP::IEventHandler::OnKeyUp(SDL_Keycode key)
{

}
//------------------------------------------------------------------------------