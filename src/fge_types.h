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
struct FGE_DistRect 
{
FGE_FRect box; 

float margin_left=0,margin_right=0, margin_top=0,margin_bottom=0; 
float padding_left=0,padding_right=0, padding_top=0,padding_bottom=0; 


inline void set_box(float x, float y, float w, float h)noexcept 
{
    box={x,y,w,h};
}
inline void set_margin(float l ,float r, float t, float b)noexcept
{
    margin_left=l; 
    margin_right=r; 
    margin_top=t; 
    margin_bottom=b;
}
inline void set_padding(float l ,float r, float t, float b)noexcept
{
    padding_left=l; 
    padding_right=r; 
    padding_top=t; 
    padding_bottom=b;
}
inline constexpr FGE_FRect get_box()const noexcept
{
    return box;
}
inline constexpr FGE_FRect get_margin_box()const noexcept
{
    return {box.x-margin_left,box.y-margin_bottom,box.w+margin_left+margin_right,box.h+margin_top+margin_bottom};
}
inline constexpr FGE_FRect get_padding_box()const noexcept
{
    return {box.x+padding_left,box.y+padding_bottom,box.w-padding_left-padding_right,box.h-padding_bottom-padding_top};
}
};


#endif