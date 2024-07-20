#ifndef FGE_WINDOW_H_
#define FGE_WINDOW_H_
/*
Sets up an OPENGL CONEXT using SDL2
*/
#define SOGL_MAJOR_VERSION 4
#define SOGL_MINOR_VERSION 5
#define SOGL_IMPLEMENTATION_WIN32

#include "ext/simple_loader.h"
#include "ext/lean_window.h"

#include <cstdint>
#include "fge_types.h"
#include <iostream>
#include "fge_time.h"

#ifdef FGE_NO_VSYNC
#define FGE_FPS_CAP 1000
#endif
#ifdef FGE_FAST_VSYNC 
#define FGE_FPS_CAP 100
#endif
#ifdef FGE_FPS_CAP
#define __FGE_FPS_CAP FGE_FPS_CAP
#else 
#define __FGE_FPS_CAP 50
#endif

#ifdef FGE_WINDOW_WIDTH
#define __FGE_WINDOWSIZE_WIDTH FGE_WINDOW_WIDTH
#else 
#define __FGE_WINDOWSIZE_WIDTH 800
#endif
#ifdef FGE_WINDOW_HEIGHT
#define __FGE_WINDOWSIZE_HEIGHT FGE_WINDOW_HEIGHT
#else 
#define __FGE_WINDOWSIZE_HEIGHT 600
#endif
#ifdef FGE_WINDOW_TITLE
#define __FGE_WINDOWSIZE_TITLE FGE_WINDOW_TITLE
#else 
#define __FGE_WINDOWSIZE_TITLE "Default Window"
#endif

namespace FGE
{


class Window{
public:
LeanWindow* window=nullptr; 
private:

LeanEvent* ev;
int wWidth=0, wHeight=0;
size_t currTime=FGE_CurrentMilliseconds();
size_t deltaTime=50;
private: 
inline void Init(const char* title, int width, int height, int flags=0)noexcept
{
    wWidth=width;
    wHeight=height; 

    window=LeanCreateWindow(title,width,height);
    ev=LeanCreateEvent();
}
public:
inline Window(const char* title, int width, int height, int flags=0)
{ 
    Init(title,width,height,flags);
}
inline Window()
{
    Init(__FGE_WINDOWSIZE_TITLE,__FGE_WINDOWSIZE_WIDTH,__FGE_WINDOWSIZE_HEIGHT);
}
inline ~Window()
{
    LeanDestroyWindow(window);
    LeanDestroyEvent(ev);
}
inline Window& SetViewport(float x, float y, float w, float h)
{
glViewport(x,y,w,h);
return *this; 
}

inline int IsRunning()
{
    deltaTime=FGE_CurrentMilliseconds()-currTime;
   
    #ifndef FGE_NO_VSYNC
    while(1000/(1+deltaTime)>__FGE_FPS_CAP)deltaTime=FGE_CurrentMilliseconds()-currTime;
    #endif

    currTime=FGE_CurrentMilliseconds();
   
    return ev->update();
}
inline void PollEvents()noexcept
{
    ev->poll();
}
inline size_t GetDeltaTime()const noexcept
{
    return deltaTime; 
}
inline size_t GetFPS()const noexcept
{
    return 1000/(1+deltaTime); 
}
inline bool KeyDown(int key)
{
    return ev->code==LEAN_KEYDOWN&&ev->key==key;
}
inline bool KeyUp(int key)
{
     return ev->code==LEAN_KEYUP&&ev->key==key;
}
inline int GetWidth()
{
    return wWidth; 
}
inline int GetHeight()
{
    return wHeight; 
}
inline Window& QueryMousePos(FGE_Point& p)
{  
    p.x=ev->cursor_x;
    p.y=ev->cursor_y;
    p.x-=wWidth/2;
    p.y=wHeight/2-p.y;
    return* this;   
}
inline Window& Swap()
{
    LeanSwapBuffers(window);
    return *this;
}
inline bool LeftClick()
{
return ev->code==LEAN_BUTTONDOWN&&ev->button==LEAN_BUTTON_LEFT;
}
inline void Show()noexcept
{
    LeanShowWindow(window);
}


};




}




#endif