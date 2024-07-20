# FGE
## What is FGE
* It is a 2D graphics library that can be used for games, guis and applications
* It is a small wrapper around OpenGL and allows you to easily interopt with the graphics card
* It is really simple to include into any existing projects, because its header only
* It has a very small byte-size, because I only use SimpleOpenGlLoader and stb_image as external libraries
## Version Info
* I switched from GLAD to SimpleOpenGlLoader, since I wanted to make this library header-only for simpler use
* The window class accesses WIN32 primitives directly and was also written by me
## How To Build
* At the moment only windows plattforms and Opengl-Version >4.5 are supported by this library (which are almost all windows plattforms)
* To build, simply include src/fge.h and you are finished (gcc requires the flags -lopengl32 -lGdi32 -municode)
## What is planned?
* TTF support
* SVG support
* GUI framework
## What happens to my compilation time, that is not best practice, you should require people to link
* We live in times where people use TypeScript and happily wait for 10 seconds, just to get js code, I think people will survive 3 seconds of compilation time
## Eyes are open for more contributors
* Currently, I am independently working on this library, so new contributors are always welcome
  

