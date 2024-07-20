# FGE
## Version Info
* I switched from GLAD to SimpleOpenGlLoader, since I wanted to make this library one-header for simpler use
* The window class accesses WIN32 primitives directly and was also written by me
## How To Build
* At the moment only windows plattforms and Opengl-Version >4.5 are supported by this library
* To build simply include src/fge.h and you are finished (gcc requires the flags -lopengl32 -lGdi32 -municode) 

