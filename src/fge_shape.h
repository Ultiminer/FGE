#ifndef FGE_SHAPE_H_
#define FGE_SHAPE_H_
#include "fge_prim_renderer.h"
#include "math.h"
#include <array>
#include <string>
#include "ext/quick_math.h"

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
/*Interface for the drawing operation and geometric manipulation of basic shapes*/



inline void fge_fill_rect(const fge_frect& rect)noexcept
{
    float vertices[]={rect.x,rect.y,
    rect.x+rect.w,rect.y, 
    rect.x+rect.w,rect.y+rect.h,
    rect.x,rect.y+rect.h,
    rect.x,rect.y};
    __FGE_PRIM_RENDER_FILL_SHAPE(vertices,5);
}
inline void fge_draw_rect(const fge_frect& rect)noexcept
{
    float vertices[]={rect.x,rect.y,
    rect.x+rect.w,rect.y, 
    rect.x+rect.w,rect.y+rect.h,
    rect.x,rect.y+rect.h,
    rect.x,rect.y};
    __FGE_PRIM_RENDER_DRAW_SHAPE(vertices,5);
}
inline void fge_draw_line(const fge_line& line)noexcept
{
    float vertices[]={line.x1,line.y1,line.x2,line.y2};
    __FGE_PRIM_RENDER_DRAW_LINE(vertices,2);
}
inline void fge_draw_lines(const std::vector<fge_line>& lines)noexcept
{
    __FGE_PRIM_RENDER_DRAW_LINE((float*)lines.data(),2*lines.size());
}
inline void fge_draw_line_strip(const std::vector<fge_fpoint>& points)noexcept
{
    __FGE_PRIM_RENDER_DRAW_SHAPE((float*)points.data(),points.size());
}
inline void fge_fill_shape(const std::vector<fge_fpoint>& points)noexcept
{
    __FGE_PRIM_RENDER_FILL_SHAPE((float*)points.data(),points.size());
}



class fge_circle_s
{
public: 
float x; float y; float r; std::array<float,1026>vertices; 
inline void UpdateShape()noexcept
{
vertices=fge_transform_vertices<1026>(__FGE_PRIMITIVE_PRELOAD_CIRCLE_DATA,x,y,r,r);
}
fge_circle_s(){}
fge_circle_s(float X, float Y, float R):x(X),y(Y),r(R){
UpdateShape();

}
inline fge_circle_s& draw()noexcept
{
    __FGE_PRIM_RENDER_FILL_SHAPE((float*)vertices.data(),513);
    return *this;
}
inline fge_circle_s& draw_border()noexcept
{
    __FGE_PRIM_RENDER_DRAW_SHAPE((float*)vertices.data(),513);
    return *this;
}
inline fge_circle_s& draw_border(const fge_color& color)noexcept
{
    fge_set_color(color);
    return  draw_border();
}
inline fge_circle_s& draw(const fge_color& color)noexcept
{
    fge_set_color(color);
    return draw();
}
inline fge_circle_s& set_x(float X)noexcept{x=X;return *this;}
inline fge_circle_s& set_y(float Y)noexcept{y=Y;return *this;}
inline fge_circle_s& set_r(float R)noexcept{r=R;return *this;}
inline fge_circle_s& shift_x(float dx)noexcept{x+=dx;return *this;}
inline fge_circle_s& shift_y(float dy)noexcept{y+=dy;return *this;}
inline fge_circle_s& lerp(const fge_fpoint& p, float lerpRate=0.01){x+=lerpRate*(p.x-x);y+=lerpRate*(p.y-y);return *this;}
inline fge_circle_s& smoothstep(const fge_fpoint& p, float stepRate=0.04){x+=fge_shape_smoothstep(stepRate*QM::tanh(p.x-x))*(p.x-x);y+=fge_shape_smoothstep(stepRate*QM::tanh(p.y-y))*(p.y-y);return *this;}

inline float get_x()const noexcept{return x;}
inline float get_y()const noexcept{return y;}
inline float get_r()const noexcept{return r;}

};
class fge_ellipse_s
{
public:
float x; float y; float a; float b; float angle; std::array<float, 1026>vertices; 

inline void UpdateShape()noexcept
{
    vertices= fge_transform_vertices<1026>(__FGE_PRIMITIVE_PRELOAD_CIRCLE_DATA, x,y,a,b,angle);
}
public:
fge_ellipse_s(){}
fge_ellipse_s(float X, float Y, float A, float B,float ANGLE=0):x(X),y(Y),a(A),b(B),angle(ANGLE){
    UpdateShape();
}
inline fge_ellipse_s& draw()noexcept
{
    __FGE_PRIM_RENDER_FILL_SHAPE((float*)vertices.data(),513);
    return *this;
}
inline fge_ellipse_s& draw(const fge_color& color)noexcept
{
    fge_set_color(color);
    return draw();
}
inline fge_ellipse_s& draw_border()noexcept
{
    __FGE_PRIM_RENDER_DRAW_SHAPE((float*)vertices.data(),513);
    return *this;
}
inline fge_ellipse_s& draw_border(const fge_color& color)noexcept
{
    fge_set_color(color); 
    return draw_border();
}
inline fge_ellipse_s& set_x(float X)noexcept{x=X; return *this;}
inline fge_ellipse_s& set_y(float Y)noexcept{y=Y; return *this;}
inline fge_ellipse_s& set_a(float A)noexcept{a=A; return *this;}
inline fge_ellipse_s& set_b(float B)noexcept{b=B; return *this;}
inline fge_ellipse_s& set_angle(float ANGLE)noexcept{angle=ANGLE; return *this;}
inline fge_ellipse_s& shift_x(float dx)noexcept{x+=dx;return *this;}
inline fge_ellipse_s& shift_y(float dy)noexcept{y+=dy;return *this;}
inline fge_ellipse_s& rotate(float dTheta)noexcept{angle+=dTheta;return *this;}
inline fge_ellipse_s& lerp(const fge_fpoint& p, float lerpRate=0.01){x+=lerpRate*(p.x-x);y+=lerpRate*(p.y-y);return *this;}
inline fge_ellipse_s& smoothstep(const fge_fpoint& p, float stepRate=0.04){x+=fge_shape_smoothstep(stepRate*QM::tanh(p.x-x))*(p.x-x);y+=fge_shape_smoothstep(stepRate*QM::tanh(p.y-y))*(p.y-y);return *this;}


inline float get_x()const noexcept{return x;}
inline float get_y()const noexcept{return y;}
inline float get_a()const noexcept{return a;}
inline float get_b()const noexcept{return b;}
inline float get_angle()const noexcept{return angle;}

};
class fge_rect_s
{
public: 
float xm; float ym; float w2; float h2;float angle;  std::array<float, 10>vertices;

inline fge_rect_s UpdateShape()noexcept
{
vertices=fge_transform_vertices<10>(__FGE_PRIMITIVE_PRELOAD_SQUARE_DATA,xm,ym,w2,h2,angle);
return *this;
}
fge_rect_s(){}
fge_rect_s(float X_M, float Y_M, float W_HALF, float H_HALF, float ANGLE=0):xm(X_M),ym(Y_M),w2(W_HALF),h2(H_HALF),angle(ANGLE){
UpdateShape();
}
inline fge_rect_s& draw()noexcept 
{
    __FGE_PRIM_RENDER_FILL_SHAPE((float*)vertices.data(),5);
    return *this;
}
inline void draw()const noexcept 
{
    __FGE_PRIM_RENDER_FILL_SHAPE((float*)vertices.data(),5);
}
inline fge_rect_s& set_rect(const fge_frect& RECT)
{
xm=RECT.x;
ym=RECT.y;
w2=RECT.w;
h2=RECT.h;
return *this;
}
inline fge_rect_s& draw(const fge_color& color)noexcept
{
    fge_set_color(color);
    return draw();
}
inline fge_rect_s& draw_border()noexcept
{
    __FGE_PRIM_RENDER_DRAW_SHAPE((float*)vertices.data(),5);
    return *this;
}
inline fge_rect_s& draw_border(const fge_color& color)noexcept
{
    fge_set_color(color);
    return draw_border();
}
inline fge_rect_s& set_xm(float XM)noexcept{xm=XM; return*this;}
inline fge_rect_s& set_ym(float YM)noexcept{ym=YM; return*this;}
inline fge_rect_s& set_w2(float W2)noexcept{w2=W2; return*this;}
inline fge_rect_s& set_h2(float H2)noexcept{h2=H2; return*this;}
inline fge_rect_s& set_angle(float ANGLE)noexcept{angle=ANGLE; return*this;}
inline fge_frect& get_rect()noexcept
{
    return (fge_frect&)*this;
}
inline fge_rect_s& shift_x(float dx)noexcept{xm+=dx;return *this;}
inline fge_rect_s& shift_y(float dy)noexcept{ym+=dy;return *this;}
inline fge_rect_s& rotate(float dTheta)noexcept{angle+=dTheta;return *this;}
inline fge_rect_s& lerp(const fge_fpoint& p, float lerpRate=0.01){xm+=lerpRate*(p.x-xm);ym+=lerpRate*(p.y-ym);return *this;}
inline fge_rect_s& smoothstep(const fge_fpoint& p, float stepRate=0.04){xm+=fge_shape_smoothstep(stepRate*QM::tanh(p.x-xm))*(p.x-xm);ym+=fge_shape_smoothstep(stepRate*QM::tanh(p.y-ym))*(p.y-ym);return *this;}

inline float get_xm()const noexcept{return xm;}
inline float get_ym()const noexcept{return ym;}
inline float get_w2()const noexcept{return w2;}
inline float get_h2()const noexcept{return h2;}
inline float get_angle()const noexcept{return angle;}
};
class fge_squircle_s
{
public: 
float x; float y; float a; float b; float angle; std::array<float,1026>vertices; 

inline void UpdateShape()noexcept
{
    vertices= fge_transform_vertices<1026>(__FGE_PRIMITIVE_PRELOAD_SQUIRCLE_DATA, x,y,a,b,angle);
}
fge_squircle_s(){}
fge_squircle_s(float X, float Y, float A, float B,float ANGLE=0):x(X),y(Y),a(A),b(B),angle{ANGLE}{
    UpdateShape();
}
inline fge_squircle_s& draw()noexcept
{
    __FGE_PRIM_RENDER_FILL_SHAPE((float*)vertices.data(),513);
    return *this;
}
inline fge_squircle_s& draw(const fge_color& color)noexcept
{ 
    fge_set_color(color);
    return draw();
}
inline fge_squircle_s& draw_border()noexcept
{
    __FGE_PRIM_RENDER_DRAW_SHAPE((float*)vertices.data(),513);
    return *this;
}
inline fge_squircle_s& draw_border(const fge_color& color)noexcept
{
    fge_set_color(color);
    return draw_border();
}
inline fge_squircle_s& set_x(float X)noexcept{x=X;return *this;}
inline fge_squircle_s& set_y(float Y)noexcept{y=Y;return *this;}
inline fge_squircle_s& set_a(float A)noexcept{a=A;return *this;}
inline fge_squircle_s& set_b(float B)noexcept{b=B;return *this;}
inline fge_squircle_s& set_angle(float ANGLE)noexcept{angle=ANGLE;return *this;}
inline fge_squircle_s& shift_x(float dx)noexcept{x+=dx;return *this;}
inline fge_squircle_s& shift_y(float dy)noexcept{y+=dy;return *this;}
inline fge_squircle_s& rotate(float dTheta)noexcept{angle+=dTheta;return *this;}
inline fge_squircle_s& lerp(const fge_fpoint& p, float lerpRate=0.01){x+=lerpRate*(p.x-x);y+=lerpRate*(p.y-y);return *this;}
inline fge_squircle_s& smoothstep(const fge_fpoint& p, float stepRate=0.04){x+=fge_shape_smoothstep(stepRate*QM::tanh(p.x-x))*(p.x-x);y+=fge_shape_smoothstep(stepRate*QM::tanh(p.y-y))*(p.y-y);return *this;}

inline float get_x()const noexcept{return x;}
inline float get_y()const noexcept{return y;}
inline float get_a()const noexcept{return a;}
inline float get_b()const noexcept{return b;}
inline float get_angle()const noexcept{return angle;}

};
class fge_triangle_s
{
public: 
fge_fpoint a,b,c;
fge_triangle_s(){}
fge_triangle_s(const fge_fpoint& A, const fge_fpoint& B, const fge_fpoint& C ):a(A),b(B),c(C){}
inline std::array<float,6> get_vertices()const noexcept
{
    return {a.x,a.y,b.x,b.y,c.x,c.y};
}

inline fge_triangle_s& draw()noexcept
{
    __FGE_PRIM_RENDER_FILL_TRIANGLE((float*)this,3);
    return *this;
}
inline fge_triangle_s& draw_border()noexcept
{
    __FGE_PRIM_RENDER_DRAW_SHAPE((float*)this,3);
    return *this;
}
inline fge_triangle_s& draw_border(const fge_color& color)noexcept
{
    fge_set_color(color);
    return  draw_border();
}
inline fge_triangle_s& draw(const fge_color& color)noexcept
{
    fge_set_color(color);
    return draw();
}
inline fge_triangle_s& set_a(const fge_fpoint& A)noexcept{a=A;return *this;}
inline fge_triangle_s& set_b(const fge_fpoint& B)noexcept{b=B;return *this;}
inline fge_triangle_s& set_c(const fge_fpoint& C)noexcept{c=C;return *this;}

inline fge_fpoint get_a()const noexcept{return a;}
inline fge_fpoint get_b()const noexcept{return b;}
inline fge_fpoint get_c()const noexcept{return c;}
};
class fge_plus_s
{
public: 
float x; float y; float l; std::array<float,26>vertices; 

fge_plus_s(){}
inline void UpdateShape()noexcept
{
vertices=fge_transform_vertices<26>(__FGE_PRIMITIVE_PRELOAD_PLUS_DATA,x,y,l,l);
}

fge_plus_s(float X, float Y, float L):x(X),y(Y),l(L){
UpdateShape();

}
inline fge_plus_s& Draw()noexcept
{
    __FGE_PRIM_RENDER_FILL_SHAPE((float*)vertices.data(),13);
    return *this;
}
inline fge_plus_s& DrawBorder()noexcept
{
    __FGE_PRIM_RENDER_DRAW_SHAPE((float*)vertices.data(),13);
    return *this;
}
inline fge_plus_s& DrawBorder(const fge_color& color)noexcept
{
    fge_set_color(color);
    return  DrawBorder();
}
inline fge_plus_s& Draw(const fge_color& color)noexcept
{
    fge_set_color(color);
    return Draw();
}
inline fge_plus_s& SetX(float X)noexcept{x=X;return *this;}
inline fge_plus_s& SetY(float Y)noexcept{y=Y;return *this;}
inline fge_plus_s& SetL(float L)noexcept{l=L;return *this;}
inline fge_plus_s& ShiftX(float dx)noexcept{x+=dx;return *this;}
inline fge_plus_s& ShiftY(float dy)noexcept{y+=dy;return *this;}
inline fge_plus_s& LERP(const fge_fpoint& p, float lerpRate=0.01){x+=lerpRate*(p.x-x);y+=lerpRate*(p.y-y);return *this;}
inline fge_plus_s& SMOOTHSTEP(const fge_fpoint& p, float stepRate=0.04){x+=fge_shape_smoothstep(stepRate*QM::tanh(p.x-x))*(p.x-x);y+=fge_shape_smoothstep(stepRate*QM::tanh(p.y-y))*(p.y-y);return *this;}

inline float GetX()const noexcept{return x;}
inline float GetY()const noexcept{return y;}
inline float GetL()const noexcept{return l;}
};

/*TODO:Fix the transition of first and last vertices*/
inline std::array<float,1026> __FGE_SRoundedRectGeneratePrimitives(const float d)
{
   std::array<float,1026>buffer={};
   constexpr size_t CIRCLE_QUARTER{256};
   
   const std::array<float,CIRCLE_QUARTER> quarter1=fge_transform_vertices<CIRCLE_QUARTER>(__FGE_PRIMITIVE_PRELOAD_CIRCLE_DATA,1-d,1-d,d,d);
   const std::array<float,CIRCLE_QUARTER> quarter2=fge_transform_vertices<CIRCLE_QUARTER>(__FGE_PRIMITIVE_PRELOAD_CIRCLE_DATA+CIRCLE_QUARTER,-(1-d),1-d,d,d);
   const std::array<float,CIRCLE_QUARTER> quarter3=fge_transform_vertices<CIRCLE_QUARTER>(__FGE_PRIMITIVE_PRELOAD_CIRCLE_DATA+2*CIRCLE_QUARTER,-(1-d),-(1-d),d,d);
   const std::array<float,CIRCLE_QUARTER> quarter4=fge_transform_vertices<CIRCLE_QUARTER>(__FGE_PRIMITIVE_PRELOAD_CIRCLE_DATA+3*CIRCLE_QUARTER,1-d,-(1-d),d,d);
   std::copy(quarter1.begin(), quarter1.end(), buffer.begin());
   std::copy(quarter2.begin(), quarter2.end(), buffer.begin()+CIRCLE_QUARTER);
   std::copy(quarter3.begin(), quarter3.end(), buffer.begin()+CIRCLE_QUARTER*2);
   std::copy(quarter4.begin(), quarter4.end(), buffer.begin()+CIRCLE_QUARTER*3);
   buffer.at(buffer.size()-2)=quarter1.at(0);
   buffer.at(buffer.size()-1)=quarter1.at(1);

   return buffer;
}

class fge_round_rect_s
{
public: 
float xm; float ym; float w2; float h2;float angle;
private: 
float d; 
public:
std::array<float,1026>vertices;
std::array<float,1026>primitive;

inline fge_round_rect_s& UpdateShape()noexcept
{
vertices=fge_transform_vertices<1026>(primitive.data(),xm,ym,w2,h2,angle);

return *this;
}
fge_round_rect_s(){
   primitive= __FGE_SRoundedRectGeneratePrimitives(d);
}
fge_round_rect_s(float X_M, float Y_M, float W_HALF, float H_HALF, float ANGLE=0,float D=0):xm(X_M),ym(Y_M),w2(W_HALF),h2(H_HALF),angle(ANGLE),d(D){
   primitive= __FGE_SRoundedRectGeneratePrimitives(d);
UpdateShape();
}
inline fge_round_rect_s& draw()noexcept 
{
    __FGE_PRIM_RENDER_FILL_SHAPE((float*)vertices.data(),vertices.size()/2);
    return *this;
}
inline void draw()const noexcept 
{
    __FGE_PRIM_RENDER_FILL_SHAPE((float*)vertices.data(),vertices.size()/2);
}
inline fge_round_rect_s& SetRect(const fge_frect& RECT)
{
xm=RECT.x;
ym=RECT.y;
w2=RECT.w;
h2=RECT.h;
return *this;
}
inline fge_round_rect_s& draw(const fge_color& color)noexcept
{
    fge_set_color(color);
    return draw();
}
inline fge_round_rect_s& draw_border()noexcept
{
    __FGE_PRIM_RENDER_DRAW_SHAPE((float*)vertices.data(),vertices.size()/2);
    return *this;
}
inline fge_round_rect_s& draw_border(const fge_color& color)noexcept
{
    fge_set_color(color);
    return draw_border();
}
inline fge_round_rect_s& set_xm(float XM)noexcept{xm=XM; return*this;}
inline fge_round_rect_s& set_ym(float YM)noexcept{ym=YM; return*this;}
inline fge_round_rect_s& set_w2(float W2)noexcept{w2=W2; return*this;}
inline fge_round_rect_s& set_h2(float H2)noexcept{h2=H2; return*this;}
inline fge_round_rect_s& set_angle(float ANGLE)noexcept{angle=ANGLE; return*this;}
inline fge_round_rect_s& set_d(float D)noexcept{d=D; 
   primitive= __FGE_SRoundedRectGeneratePrimitives(d);
return*this;}

inline fge_round_rect_s& shift_x(float dx)noexcept{xm+=dx;return *this;}
inline fge_round_rect_s& shift_y(float dy)noexcept{ym+=dy;return *this;}
inline fge_round_rect_s& rotate(float dTheta)noexcept{angle+=dTheta;return *this;}
inline fge_round_rect_s& lerp(const fge_fpoint& p, float lerpRate=0.01){xm+=lerpRate*(p.x-xm);ym+=lerpRate*(p.y-ym);return *this;}
inline fge_round_rect_s& smoothstep(const fge_fpoint& p, float stepRate=0.04){xm+=fge_shape_smoothstep(stepRate*QM::tanh(p.x-xm))*(p.x-xm);ym+=fge_shape_smoothstep(stepRate*QM::tanh(p.y-ym))*(p.y-ym);return *this;}

inline float get_xm()const noexcept{return xm;}
inline float get_ym()const noexcept{return ym;}
inline float get_w2()const noexcept{return w2;}
inline float get_h2()const noexcept{return h2;}
inline float get_angle()const noexcept{return angle;}
inline float get_d()const noexcept{return d;}

};





#endif