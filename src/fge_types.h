#ifndef FGE_SDL_TYPES_H_
#define FGE_SDL_TYPES_H_

struct fge_fpoint{
float x; float y; 
};
struct fge_point{
int x; int y; 
};
struct fge_rect{
int x; int y; int w; int h; 
};
struct fge_frect{
float x; float y; float w; float h; 
};
struct fge_color{
unsigned char r; unsigned char g; unsigned char b;unsigned char a; 
};

struct fge_line{float x1; float y1; float x2; float y2;};



#endif