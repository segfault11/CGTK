/*!
** Definition of a default SDL application.
**  
** @file SDLApplication.h
** @since 2013-08-15 
*/
#ifndef SDLAPPLICATION_H__
#define SDLAPPLICATION_H__

#include <SDL2/SDL.h>
#include "IEventHandler.h"
#include "IDrawable.h"
#include "Camera.h"
#include <list>

namespace APP
{
    /*!
    ** Initialize the application. Creates a window and an OpenGL 3.2 context.
    ** 
    ** @param name Name of the applications (title of the window).
    ** @param x x position of the window.
    ** @param y y position of the window.
    ** @param width width of the window.
    ** @param height height of the window.
    **
    ** @since 2013-08-15 
    */
    void Init(
        const char* name, 
        unsigned int x, 
        unsigned int y, 
        unsigned int width, 
        unsigned int height
    );
        
    void Destroy();

    /*!
    ** Enters the main loop of the application.
    **  
    ** @since 2013-08-15
    */
    void Run();

    void SetCamera(const Camera& camera);
    Camera& GetCamera();

    void RegisterDrawable(IDrawable& drawable);
    void RegisterGUIElement(IDrawable& drawable);
    void RegisterEventHandler(IEventHandler& eventHandler);

    unsigned int GetScreenWidth();
    unsigned int GetScreenHeight();

    bool IsInitialized();

    float GetDeltaTime();

}

#endif /* end of include guard: SDLAPPLICATION_H__ */