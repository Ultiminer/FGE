# FGE
## What is FGE
* It is a 2D graphics library that can be used for games, guis and applications
* It is a small wrapper around OpenGL and allows you to easily interopt with the graphics card
* It is really simple to include into any existing projects, because its header only
* It has a very small byte-size, because I only use SimpleOpenGlLoader and stb_image as external libraries
## Version Info
* I switched from GLAD to SimpleOpenGlLoader, since I wanted to make this library one-header for simpler use
* The window class accesses WIN32 primitives directly and was also written by me
## How To Build
* At the moment only windows plattforms and Opengl-Version >4.5 are supported by this library (which are almost all windows plattforms)
* To build, simply include src/fge.h and you are finished (gcc requires the flags -lopengl32 -lGdi32 -municode) 

