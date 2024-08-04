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
#include "fge_prim_renderer.h"

#ifdef FGE_NO_VSYNC
#define FGE_FPS_CAP 1000
#endif
#ifdef FGE_FAST_VSYNC 
#define FGE_FPS_CAP 100
#endif
#ifdef FGE_FPS_CAP
#define __FGE_FPS_CAP FGE_FPS_CAP
#else 
#define __FGE_FPS_CAP 60
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



class fge_window{
public:
LeanWindow* window=nullptr; 
private:

LeanEvent* ev;
int wWidth=0, wHeight=0;
size_t currTime=fge_current_milliseconds();
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
inline fge_window(const char* title, int width, int height, int flags=0)
{ 
    Init(title,width,height,flags);
}
inline fge_window()
{
    Init(__FGE_WINDOWSIZE_TITLE,__FGE_WINDOWSIZE_WIDTH,__FGE_WINDOWSIZE_HEIGHT);
}
inline ~fge_window()
{
    LeanDestroyWindow(window);
    LeanDestroyEvent(ev);
}
inline fge_window& set_viewport(float x, float y, float w, float h)
{
glViewport(x,y,w,h);
return *this; 
}

inline int is_running()
{
    deltaTime=fge_current_milliseconds()-currTime;

    /*
    Polling size change events from the WIN32 APi 
    and Updating renderers
    */
    const int nWidth=LeanGetWidth(window),nHeight=LeanGetHeight(window);
    if(nWidth*nHeight!=0)
    {
    if(nWidth!=wWidth||nHeight!=wHeight)
    {
    wWidth=nWidth;
    wHeight=nHeight;
    fge::send_window_size(wWidth,wHeight);
    }
    }

    #ifndef FGE_NO_VSYNC
    Sleep(2);
    while(1000/(1+deltaTime)>__FGE_FPS_CAP){deltaTime=fge_current_milliseconds()-currTime;}
    #else 
    deltaTime=fge_current_milliseconds()-currTime;
    #endif
    
    currTime=fge_current_milliseconds();
   
    return ev->update();
}
inline fge_window& poll_events()noexcept
{
    ev->poll();
    return *this;
}
inline size_t get_delta_time()const noexcept
{
    return deltaTime; 
}
inline size_t get_fps()const noexcept
{
    return 1000/(1+deltaTime); 
}
inline bool key_down(int key)
{
    return ev->code==LEAN_KEYDOWN&&ev->key==key;
}
inline bool key_up(int key)
{
     return ev->code==LEAN_KEYUP&&ev->key==key;
}
inline int get_width()
{
    return wWidth; 
}
inline int get_height()
{
    return wHeight; 
}
inline fge_window& get_cursor(int&x , int& y)
{  
    LeanGetCursor(window,x,y);
    /*Changing the coordinates from top-left to centered*/
    x-=wWidth/2;
    y=wHeight/2-y;
    return* this;   
}
inline fge_window& swap()
{
    LeanSwapBuffers(window);
    return *this;
}
inline bool left_click()
{
return ev->code==LEAN_BUTTONDOWN&&ev->button==LEAN_BUTTON_LEFT;
}
inline fge_window& show()noexcept
{
    LeanShowWindow(window);
    return *this;
}


};








#endif