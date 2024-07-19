#ifndef FGE_SDL_TYPES_H_
#define FGE_SDL_TYPES_H_

struct FGE_FPoint{
float x; float y; 
};
struct FGE_Point{
int x; int y; 
};
struct FGE_Rect{
int x; int y; int w; int h; 
};
struct FGE_FRect{
float x; float y; float w; float h; 
};
struct FGE_Color{
unsigned char r; unsigned char g; unsigned char b;unsigned char a; 
};
struct FGE_Circle{float x; float y; float r;};
struct FGE_Ellipse{float x; float y; float a; float b;};

struct FGE_Triangle{FGE_FPoint a; FGE_FPoint b; FGE_FPoint c; };
struct FGE_Line{float x1; float y1; float x2; float y2;};
struct FGE_Squircle{float x; float y; float a; float n;};


#endif