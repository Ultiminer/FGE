#ifndef FGE_WINDOW_H_
#define FGE_WINDOW_H_
/*
Sets up an OPENGL CONEXT using SDL2
*/
#include "ext/glew.h"
#include "ext/glfw3.h"
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
GLFWwindow* window=nullptr; 
int wWidth=0, wHeight=0;
size_t currTime=FGE_CurrentMilliseconds();
size_t deltaTime=50;
private: 
inline void Init(const char* title, int width, int height, int flags=0)noexcept
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(width, height, "Hello World",NULL, NULL);
    glfwWindowHint(flags,1);
    if (!window)
    {
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window);
    GLenum err = glewInit();
    if (err!=GLEW_OK)
    {
    std::cout << "Failed to initialize GLEW" << std::endl;
    exit(-1);
    }  

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
    glfwDestroyWindow(window);
    glfwTerminate();
}
inline Window& SetViewport(float x, float y, float w, float h)
{
glViewport(x,y,w,h);
return *this; 
}
inline Window& PollEvents()
{
    glfwPollEvents();

    return *this;
}

inline Window& SetTitle(const char* title)
{
    glfwSetWindowTitle(window, title);
    return *this;
}
inline bool IsRunning()
{
    deltaTime=FGE_CurrentMilliseconds()-currTime;

    #ifndef FGE_NO_VSYNC
    while(1000/(1+deltaTime)>__FGE_FPS_CAP)deltaTime=FGE_CurrentMilliseconds()-currTime;
    #endif

    currTime=FGE_CurrentMilliseconds();

    return !glfwWindowShouldClose(window);
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
    return glfwGetKey(window,key)==GLFW_PRESS;
}
inline bool KeyUp(int key)
{
    return glfwGetKey(window,key)==GLFW_RELEASE;
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
    glfwGetCursorPos(window,(double*)&p.x,(double*)&p.y);
    p.x-=wWidth/2;
    p.y=wHeight/2-p.y;
    return* this;   
}
inline Window& SetWidth(int width)
{
    glfwSetWindowSize(window,width,wHeight);
    wWidth=width;
    return *this;
}
inline Window& SetHeight(int height)
{
    glfwSetWindowSize(window,wWidth,height);
    wHeight=height;

    return *this;
}
inline Window& SetSize(int width, int height)
{
    glfwSetWindowSize(window,width,height);
    wWidth=width; wHeight=height; 
    return *this;
}
inline Window& Hint(int name, int value)
{
    glfwWindowHint(name,value);
    return *this;
}

inline Window& Swap()
{
     glfwSwapBuffers(window);
    return *this;
}
inline bool LeftClick()
{
return glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_LEFT)==GLFW_PRESS;
}



};




}




#endif