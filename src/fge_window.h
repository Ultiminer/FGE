#ifndef FGE_WINDOW_H_
#define FGE_WINDOW_H_
/*
Sets up an OPENGL CONEXT using SDL2
*/

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


private:
SDL_Surface* iconSurface=nullptr;
SDL_Window* sdlWindow=nullptr; 
SDL_Event* sdlEvent=nullptr; 
int wWidth=0, wHeight=0;
SDL_GLContext ctx; 
size_t currTime=FGE_CurrentMilliseconds();
size_t deltaTime=50;
bool UpKey=false; 
public:
inline Window(const char* title, int width, int height, Uint32 flags=0)
{
SDL_Init(SDL_INIT_VIDEO);
SDL_GL_LoadLibrary(NULL);
SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_CORE);
SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

sdlWindow=SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, width,height,flags|SDL_WINDOW_OPENGL );
sdlEvent= new SDL_Event();
wWidth=width; wHeight=height;

ctx=SDL_GL_CreateContext(sdlWindow);
gladLoadGLLoader(SDL_GL_GetProcAddress);
SDL_GL_SetSwapInterval(0);
glClearColor(1,0.46,0.8,1);



}
inline Window()
{
SDL_Init(SDL_INIT_VIDEO);
SDL_GL_LoadLibrary(NULL);
SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_CORE);
SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

sdlWindow=SDL_CreateWindow(__FGE_WINDOWSIZE_TITLE,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, __FGE_WINDOWSIZE_WIDTH,__FGE_WINDOWSIZE_HEIGHT, SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL);
sdlEvent= new SDL_Event();
wWidth=__FGE_WINDOWSIZE_WIDTH; wHeight=__FGE_WINDOWSIZE_HEIGHT;

ctx=SDL_GL_CreateContext(sdlWindow);
gladLoadGLLoader(SDL_GL_GetProcAddress);
SDL_GL_SetSwapInterval(0);
glClearColor(1,0.46,0.8,1);


}
inline ~Window()
{
    SDL_FreeSurface(iconSurface);
    delete iconSurface;
    SDL_Quit();
    SDL_DestroyWindow(sdlWindow);
    delete sdlEvent;
}
inline Window& SetViewport(float x, float y, float w, float h)
{
glViewport(x,y,w,h);
return *this; 
}
inline Window& PollEvents()
{
    SDL_PollEvent(sdlEvent);
    if(sdlEvent->type==SDL_KEYDOWN&&sdlEvent->key.keysym.sym==SDLK_LSHIFT)UpKey=true;
    if(sdlEvent->type==SDL_KEYUP&&sdlEvent->key.keysym.sym==SDLK_LSHIFT)UpKey=false;

    return *this;
}
constexpr bool GetUpKey()const
{
    return UpKey;
}
inline Window& SetTitle(const char* title)
{
    SDL_SetWindowTitle(sdlWindow, title);
    return *this;
}
inline bool IsRunning()
{
    deltaTime=FGE_CurrentMilliseconds()-currTime;

    #ifndef FGE_NO_VSYNC
    while(1000/(1+deltaTime)>__FGE_FPS_CAP)deltaTime=FGE_CurrentMilliseconds()-currTime;
    #endif

    currTime=FGE_CurrentMilliseconds();

    return sdlEvent->type!=SDL_QUIT;
}
inline size_t GetDeltaTime()const noexcept
{
    return deltaTime; 
}
inline size_t GetFPS()const noexcept
{
    return 1000/(1+deltaTime); 
}
inline bool KeyDown(long long int key)
{
    if(sdlEvent->type!=SDL_KEYDOWN)return false;
    return sdlEvent->key.keysym.sym==key;
}
inline bool KeyUp(long long int key)
{
    if(sdlEvent->type!=SDL_KEYUP)return false;
    return sdlEvent->key.keysym.sym==key;
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
    SDL_GetMouseState(&p.x,&p.y);
    p.x-=wWidth/2;
    p.y=wHeight/2-p.y;
    return* this;   
}
inline Window& SetWidth(int width)
{
    SDL_SetWindowSize(sdlWindow,width,wHeight);
    wWidth=width;
    return *this;
}
inline Window& SetHeight(int height)
{
    SDL_SetWindowSize(sdlWindow,wWidth,height);
    wHeight=height;

    return *this;
}
inline Window& SetSize(int width, int height)
{
    SDL_SetWindowSize(sdlWindow,width,height);
    wWidth=width; wHeight=height; 
    return *this;
}
inline Window& Hint(const char* name, const char* value)
{
    SDL_SetHint(name,value);
    return *this;
}
inline Window& OnTop()
{
    SDL_SetWindowAlwaysOnTop(sdlWindow,(SDL_bool)true);
    return *this;
}
inline Window& NotOnTop()
{
    SDL_SetWindowAlwaysOnTop(sdlWindow,(SDL_bool)false);
    return *this;
}
inline Window& Bordered()
{
    SDL_SetWindowBordered(sdlWindow,(SDL_bool)true);
    return *this;
}
inline Window& UnBordered()
{
    SDL_SetWindowBordered(sdlWindow,(SDL_bool)false);
    return *this;
}
inline Window& SetBrightness(float brightness)
{
    SDL_SetWindowBrightness(sdlWindow, brightness);
    return *this;
}
inline Window& SetDisplayMode(const SDL_DisplayMode& mode)
{
    SDL_SetWindowDisplayMode(sdlWindow,&mode);
    return *this;
}
inline Window& Fullscreen()
{
    SDL_SetWindowFullscreen(sdlWindow,SDL_WINDOW_FULLSCREEN_DESKTOP);
    SDL_GetWindowSize(sdlWindow,&wWidth,&wHeight);

    return *this;
}
inline Window& GrabInput()
{
    SDL_SetWindowGrab(sdlWindow,(SDL_bool)true);
    return *this;
}
inline Window& UnGrabInput()
{
    SDL_SetWindowGrab(sdlWindow,(SDL_bool)false);
    return *this;
}
inline Window& SetIcon(const char* path)
{
    iconSurface=SDL_LoadBMP(path);
    SDL_SetWindowIcon(sdlWindow,iconSurface);
    return *this;
}
inline Window& GrabMouse()
{
    SDL_SetWindowMouseGrab(sdlWindow,(SDL_bool)true);
    return *this;
}
inline Window& UnGrabMouse()
{
    SDL_SetWindowMouseGrab(sdlWindow,(SDL_bool)false);
    return *this;
}
inline Window& SetOpacity(float opacity)
{
    SDL_SetWindowOpacity(sdlWindow,opacity);
    return *this;
}
inline Window& SetResizable(bool resizable)
{
    SDL_SetWindowResizable(sdlWindow, (SDL_bool)resizable);
    return *this;
}
inline Window& Swap()
{
    SDL_GL_SwapWindow(sdlWindow);
    return *this;
}
inline bool LeftClick()
{
return (sdlEvent->type==SDL_MOUSEBUTTONDOWN&&sdlEvent->button.button==SDL_BUTTON_LEFT);
}



};




}




#endif