# FGE
## What is FGE
* It is a 2D graphics library that can be used for games, guis and applications
* It is a small wrapper around OpenGL and allows you to easily interopt with the graphics card
* It is really simple to include into any existing projects, because its header only (provides no extra linking overhead)
* It has a very small byte-size, because I only use SimpleOpenGlLoader and stb_image as external libraries
## Version Info
* I switched from GLAD to SimpleOpenGlLoader, since I wanted to make this library header-only for simpler use
* The window class accesses WIN32 primitives directly and was also written by me
## How To Build
* At the moment only windows plattforms and Opengl-Version >4.5 are supported by this library (which are almost all windows plattforms)
* To build, simply include src/fge.h and you are finished (gcc requires the flags -lopengl32 -lGdi32 -municode)
* Either MINGW should be installed/linked or the dll's corresponding to opengl32, Gdi32 and unicode, windows machines should have those libraries pre-installed though
* No external linking is required though, and it should actually work out of the box with any normal setup and obviously with visual studio IDE, since the dlls are linked per default there
## Newly added features
* Monospaced font rendering with costumary colors
## What is planned?
* Screenshot function
* SVG support
## What happens to my compilation time, that is not best practice, you should require people to link
* We live in times where people use TypeScript and happily wait for 10 seconds, just to get js code, I think people will survive 3 seconds of compilation time
## Eyes are open for more contributors
* Currently, I am independently working on this library, so new contributors are always welcome
  

