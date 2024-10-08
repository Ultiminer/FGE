#ifndef LEAN_WINDOW_H_
#define LEAN_WINDOW_H_

#define WIN32_LEAN_AND_MEAN 1
#define SOGL_IMPLEMENTATION
/*
BSD 3-Clause License

Copyright (c) 2024, FloDev

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "Windows.h"
#include <iostream>
#include <cstdint>
#include <wingdi.h>
#include "wglext.h"
#include <thread>
#define main lean_main
int main(int, char**);

typedef PROC (*wglGetProcAddressFP)(LPCSTR Arg1);
static HMODULE openGLLibHandle = NULL;
wchar_t *char_to_wchar(const char* charArray)
{
    wchar_t* wString=new wchar_t[4096];
    MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
    return wString;
}

#define DECLARE_WGL_EXT_FUNC(returnType, name, ...) typedef returnType (WINAPI *name##FUNC)(__VA_ARGS__);\
    name##FUNC name = (name##FUNC)0;
#define LOAD_WGL_EXT_FUNC(name) name = (name##FUNC) wglGetProcAddress(#name)
DECLARE_WGL_EXT_FUNC(BOOL, wglChoosePixelFormatARB, HDC hdc, const int *piAttribIList, const FLOAT *pfAttribFList, UINT nMaxFormats, int *piFormats, UINT *nNumFormats);
DECLARE_WGL_EXT_FUNC(HGLRC, wglCreateContextAttribsARB, HDC hDC, HGLRC hshareContext, const int *attribList);
inline struct __WIN_INFO{HINSTANCE hInstance; HINSTANCE hPrevInstance; LPCWSTR pCmdLine; int nCmdShow;}__win_info;
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    __win_info={hInstance,hPrevInstance,pCmdLine,nCmdShow};
    
    return lean_main(nCmdShow,(char**)pCmdLine);
}

inline struct LeanEvent
{
    int key; 
    unsigned int wParam; 
    MSG msg; 
    uint32_t code;
    inline int update()noexcept
    {
    return GetMessage(&msg, NULL, 0, 0);
    }
    inline void poll()noexcept
    {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
    }
}__lean_event;
#define LEAN_BUTTONDOWN WM_LBUTTONDOWN
#define LEAN_LBUTTONUP WM_LBUTTONUP
#define LEAN_LBUTTONDOWN WM_LBUTTONDOWN
#define LEAN_RBUTTONUP WM_RBUTTONUP
#define LEAN_RBUTTONDOWN WM_RBUTTONDOWN
#define LEAN_MBUTTONUP WM_MBUTTONUP
#define LEAN_MBUTTONDOWN WM_MBUTTONDOWN
#define LEAN_KEYDOWN WM_KEYDOWN
#define LEAN_KEYUP WM_KEYUP


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    {
    __lean_event.wParam=wParam;
    __lean_event.code=uMsg;
    __lean_event.key=   GET_KEYSTATE_WPARAM(wParam);
    }
    switch (uMsg)
    {
      case WM_SIZING: {
            return 0;
        } break;
        case WM_PAINT: {
        return 0;
          
        } break;
        case WM_CLOSE: {
            PostQuitMessage(0);
            return 0;
        } break;
        case WM_ERASEBKGND:
        { 
           auto context= GetDC(hwnd);
        return TRUE;}
        break;
    }
    
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

struct LeanWindow
{
WNDCLASSEXW wc={0}; 
HWND hwnd;
HDC hdc; 
HGLRC hglrc;
};

inline LeanEvent* LeanCreateEvent()noexcept
{
    return &__lean_event;
}
inline void LeanDestroyEvent(LeanEvent* ev)noexcept
{
}
inline LeanWindow* LeanCreateWindow(const char* title="Std", int width=CW_USEDEFAULT, int height=CW_USEDEFAULT)noexcept
{
    /*
    CREATING WC
    ------------------------------------------------------------------------
    */
    LeanWindow* wnd= new LeanWindow();
    wnd->wc.cbSize = sizeof(wnd->wc);
    wnd->wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wnd->wc.lpfnWndProc = WindowProc;
    wnd->wc.hInstance = __win_info.hInstance;
    wnd->wc.hIcon = LoadIcon(__win_info.hInstance, IDI_APPLICATION);
    wnd->wc.hIconSm = LoadIcon(__win_info.hInstance, IDI_APPLICATION);
    wnd->wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wnd->wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wnd->wc.lpszClassName = L"WINDOW_CLASS";
    RegisterClassExW(&wnd->wc);
    /*
        DUMMY WINDOW CREATION FOR MFCINF OPENGL TO WORK CAUS WIN32 DEVS ARE SILLY 
        --------------------------------------------------------------------------
    */
    HWND dummyWindow = CreateWindowExW(0,wnd->wc.lpszClassName, L"DUMMY", WS_OVERLAPPEDWINDOW, 0, 0, 1, 1, NULL,  NULL, __win_info.hInstance, NULL);

    if (!dummyWindow) {
    std::cout<<"Failed to create window\n"<<std::flush;
    exit(-1);
    }

    HDC dummyContext = GetDC(dummyWindow);

    PIXELFORMATDESCRIPTOR pfd = {0};
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
    pfd.iPixelType = PFD_TYPE_RGBA,        
    pfd.cColorBits = 32;                   
    pfd.cDepthBits = 24;           
    pfd.cStencilBits = 8;                 
    pfd.iLayerType = PFD_MAIN_PLANE;
    
    int pixelFormat = ChoosePixelFormat(dummyContext, &pfd);
    SetPixelFormat(dummyContext, pixelFormat, &pfd);
    HGLRC dummyGL = wglCreateContext(dummyContext);
    wglMakeCurrent(dummyContext, dummyGL);

    LOAD_WGL_EXT_FUNC(wglChoosePixelFormatARB);
    LOAD_WGL_EXT_FUNC(wglCreateContextAttribsARB);

    if (!wglCreateContextAttribsARB || !wglCreateContextAttribsARB) {
        std::cout<<"Failed to get args\n"<<std::flush;
        exit(-1);
    }

    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(dummyGL);
    DestroyWindow(dummyWindow);

    /*
    ACTUAL WINDOW CREATION 
    ------------------------------------------------------------------------------
    ------------------------------------------------------------------------------
    */


    
    wnd->hwnd = CreateWindowExW(
    0,                              // Optional window styles.
    wnd->wc.lpszClassName,                     // Window class
    char_to_wchar(title),    // Window text
    WS_OVERLAPPEDWINDOW,            // Window style

    // Size and position
    CW_USEDEFAULT,CW_USEDEFAULT, width, height,

    NULL,       // Parent window    
    NULL,       // Menu
    __win_info.hInstance,  // Instance handle
    NULL        // Additional application data
    );

    if (wnd->hwnd == NULL)
    {
    std::cout<<"WINDOW WAS NULL"<<std::endl;
    exit(-1);
    }
    
    wnd->hdc = GetDC(wnd->hwnd);

    const int pixelAttribList[] = {
        WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
        WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
        WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
        WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
        WGL_COLOR_BITS_ARB, 32,
        WGL_DEPTH_BITS_ARB, 24,
        WGL_STENCIL_BITS_ARB, 8,
        WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
        WGL_SAMPLE_BUFFERS_ARB, GL_TRUE,
        WGL_SAMPLES_ARB, 4,
        0
    };

    UINT numFormats;
    BOOL success;
    success = wglChoosePixelFormatARB(wnd->hdc, pixelAttribList, NULL, 1, &pixelFormat, &numFormats);

    if (!success || numFormats == 0) {
        std::cout<<"Could not load Pixel Format\n"<<std::flush;
        exit(EXIT_FAILURE);
    }
    
    DescribePixelFormat(wnd->hdc, pixelFormat, sizeof(pfd), &pfd);
    SetPixelFormat(wnd->hdc, pixelFormat, &pfd);

    const int contextAttribList[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
        WGL_CONTEXT_MINOR_VERSION_ARB, 5,
        WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0
    };

    wnd->hglrc = wglCreateContextAttribsARB(wnd->hdc, NULL, contextAttribList);

    if (!wnd->hglrc) {
        std::cout<<"Could not load ARB context\n"<<std::flush;
        exit(EXIT_FAILURE);
    }

    wglMakeCurrent(wnd->hdc, wnd->hglrc);
    
    if (!sogl_loadOpenGL()) {
        const char **failures = sogl_getFailures();
        while (*failures) {
            char debugMessage[256];
            snprintf(debugMessage, 256, "SOGL WIN32 EXAMPLE: Failed to load function %s\n", *failures);
            OutputDebugStringA(debugMessage);
            failures++;
        }
    }
    glViewport(0, 0, width, height);
    return wnd; 
}
inline void LeanDestroyWindow(LeanWindow* wind)noexcept
{
    wglDeleteContext(
    wind->hglrc
    );
    delete wind; 
}
inline int LeanGetWidth(LeanWindow* wind)noexcept
{
  RECT rct;
  
 GetClientRect(wind->hwnd, &rct);
 return rct.right-rct.left;
}
inline int LeanGetHeight(LeanWindow* wind)noexcept
{
  RECT rct;
 GetClientRect(wind->hwnd, &rct);
 return rct.bottom-rct.top;
}
inline void LeanGetSize(LeanWindow* wind, int& x, int& y)noexcept
{
    RECT rct;
 GetClientRect(wind->hwnd, &rct);
 x=rct.right-rct.left;
 y=rct.bottom-rct.top; 
}
inline void LeanGetCursor(LeanWindow* wind, int& x, int& y)noexcept
{
    POINT p;
    GetCursorPos(&p);
    ScreenToClient(wind->hwnd, &p);
    x=(int)p.x;
    y=(int)p.y;
}
inline void LeanShowWindow(LeanWindow* wind)noexcept
{
    ShowWindow(wind->hwnd, __win_info.nCmdShow);
}
inline bool LeanSwapBuffers(LeanWindow*wnd)noexcept
{
    return SwapBuffers(
     wnd->hdc
    );
}
inline void LeanGetMetrics(int& w, int& h)noexcept
{
    w=GetSystemMetrics(SM_CXSCREEN);
    h=GetSystemMetrics(SM_CYSCREEN);
}
#endif