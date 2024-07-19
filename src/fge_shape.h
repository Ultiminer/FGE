#ifndef FGE_SHAPE_H_
#define FGE_SHAPE_H_
#include "fge_prim_renderer.h"
#include "math.h"
#include <array>
#include <string>
#include "quick_math.h"


/*Interface for the drawing operation and geometric manipulation of basic shapes*/
/*
-----------TODO----------------
>Transform the vertices every time position or object size changes, so there is no need for extensive uniform overloading 
>Add more shapes + Possibility to draw thick circle arcs and thick shape borders
>Mimic every css functionality
*/


namespace FGE{




class SCircle
{
public: 
float x; float y; float r; std::array<float,1026>vertices; 
inline void UpdateShape()noexcept
{
vertices=TransformVertices<1026>(__FGE_PRIMITIVE_PRELOAD_CIRCLE_DATA,x,y,r,r);
}
SCircle(){}
SCircle(float X, float Y, float R):x(X),y(Y),r(R){
UpdateShape();

}
inline SCircle& Draw()noexcept
{
    __FGE_PRIM_RENDER_FILL_SHAPE((float*)vertices.data(),513);
    return *this;
}
inline SCircle& DrawBorder()noexcept
{
    __FGE_PRIM_RENDER_DRAW_SHAPE((float*)vertices.data(),513);
    return *this;
}
inline SCircle& DrawBorder(const FGE_Color& color)noexcept
{
    FGE_SetColor(color);
    return  DrawBorder();
}
inline SCircle& Draw(const FGE_Color& color)noexcept
{
    FGE_SetColor(color);
    return Draw();
}
inline SCircle& SetX(float X)noexcept{x=X;return *this;}
inline SCircle& SetY(float Y)noexcept{y=Y;return *this;}
inline SCircle& SetR(float R)noexcept{r=R;return *this;}
inline SCircle& ShiftX(float dx)noexcept{x+=dx;return *this;}
inline SCircle& ShiftY(float dy)noexcept{y+=dy;return *this;}
inline SCircle& LERP(const FGE_FPoint& p, float lerpRate=0.01){x+=lerpRate*(p.x-x);y+=lerpRate*(p.y-y);return *this;}
inline SCircle& SMOOTHSTEP(const FGE_FPoint& p, float stepRate=0.04){x+=SHAPE_SMOOTHSTEP(stepRate*QM::tanh(p.x-x))*(p.x-x);y+=SHAPE_SMOOTHSTEP(stepRate*QM::tanh(p.y-y))*(p.y-y);return *this;}

inline float GetX()const noexcept{return x;}
inline float GetY()const noexcept{return y;}
inline float GetR()const noexcept{return r;}

};
class SEllipse
{
public:
float x; float y; float a; float b; float angle; std::array<float, 1026>vertices; 

inline void UpdateShape()noexcept
{
    vertices= TransformVertices<1026>(__FGE_PRIMITIVE_PRELOAD_CIRCLE_DATA, x,y,a,b,angle);
}
public:
SEllipse(){}
SEllipse(float X, float Y, float A, float B,float ANGLE=0):x(X),y(Y),a(A),b(B),angle(ANGLE){
    UpdateShape();
}
inline SEllipse& Draw()noexcept
{
    __FGE_PRIM_RENDER_FILL_SHAPE((float*)vertices.data(),513);
    return *this;
}
inline SEllipse& Draw(const FGE_Color& color)noexcept
{
    FGE_SetColor(color);
    return Draw();
}
inline SEllipse& DrawBorder()noexcept
{
    __FGE_PRIM_RENDER_DRAW_SHAPE((float*)vertices.data(),513);
    return *this;
}
inline SEllipse& DrawBorder(const FGE_Color& color)noexcept
{
    FGE_SetColor(color); 
    return DrawBorder();
}
inline SEllipse& SetX(float X)noexcept{x=X; return *this;}
inline SEllipse& SetY(float Y)noexcept{y=Y; return *this;}
inline SEllipse& SetA(float A)noexcept{a=A; return *this;}
inline SEllipse& SetB(float B)noexcept{b=B; return *this;}
inline SEllipse& SetAngle(float ANGLE)noexcept{angle=ANGLE; return *this;}
inline SEllipse& ShiftX(float dx)noexcept{x+=dx;return *this;}
inline SEllipse& ShiftY(float dy)noexcept{y+=dy;return *this;}
inline SEllipse& Rotate(float dTheta)noexcept{angle+=dTheta;return *this;}
inline SEllipse& LERP(const FGE_FPoint& p, float lerpRate=0.01){x+=lerpRate*(p.x-x);y+=lerpRate*(p.y-y);return *this;}
inline SEllipse& SMOOTHSTEP(const FGE_FPoint& p, float stepRate=0.04){x+=SHAPE_SMOOTHSTEP(stepRate*QM::tanh(p.x-x))*(p.x-x);y+=SHAPE_SMOOTHSTEP(stepRate*QM::tanh(p.y-y))*(p.y-y);return *this;}


inline float GetX()const noexcept{return x;}
inline float GetY()const noexcept{return y;}
inline float GetA()const noexcept{return a;}
inline float GetB()const noexcept{return b;}
inline float GetAngle()const noexcept{return angle;}

};
class SRect
{
public: 
float xm; float ym; float w2; float h2;float angle;  std::array<float, 10>vertices;

inline SRect UpdateShape()noexcept
{
vertices=TransformVertices<10>(__FGE_PRIMITIVE_PRELOAD_SQUARE_DATA,xm,ym,w2,h2,angle);
return *this;
}
SRect(){}
SRect(float X_M, float Y_M, float W_HALF, float H_HALF, float ANGLE=0):xm(X_M),ym(Y_M),w2(W_HALF),h2(H_HALF),angle(ANGLE){
UpdateShape();
}
inline SRect& Draw()noexcept 
{
    __FGE_PRIM_RENDER_FILL_SHAPE((float*)vertices.data(),5);
    return *this;
}
inline void Draw()const noexcept 
{
    __FGE_PRIM_RENDER_FILL_SHAPE((float*)vertices.data(),5);
}
inline SRect& SetRect(const FGE_FRect& RECT)
{
xm=RECT.x;
ym=RECT.y;
w2=RECT.w;
h2=RECT.h;
return *this;
}
inline SRect& Draw(const FGE_Color& color)noexcept
{
    FGE_SetColor(color);
    return Draw();
}
inline SRect& DrawBorder()noexcept
{
    __FGE_PRIM_RENDER_DRAW_SHAPE((float*)vertices.data(),5);
    return *this;
}
inline SRect& DrawBorder(const FGE_Color& color)noexcept
{
    FGE_SetColor(color);
    return DrawBorder();
}
inline SRect& SetXM(float XM)noexcept{xm=XM; return*this;}
inline SRect& SetYM(float YM)noexcept{ym=YM; return*this;}
inline SRect& SetW2(float W2)noexcept{w2=W2; return*this;}
inline SRect& SetH2(float H2)noexcept{h2=H2; return*this;}
inline SRect& SetAngle(float ANGLE)noexcept{angle=ANGLE; return*this;}
inline FGE_FRect& GetRect()noexcept
{
    return (FGE_FRect&)*this;
}
inline SRect& ShiftX(float dx)noexcept{xm+=dx;return *this;}
inline SRect& ShiftY(float dy)noexcept{ym+=dy;return *this;}
inline SRect& Rotate(float dTheta)noexcept{angle+=dTheta;return *this;}
inline SRect& LERP(const FGE_FPoint& p, float lerpRate=0.01){xm+=lerpRate*(p.x-xm);ym+=lerpRate*(p.y-ym);return *this;}
inline SRect& SMOOTHSTEP(const FGE_FPoint& p, float stepRate=0.04){xm+=SHAPE_SMOOTHSTEP(stepRate*QM::tanh(p.x-xm))*(p.x-xm);ym+=SHAPE_SMOOTHSTEP(stepRate*QM::tanh(p.y-ym))*(p.y-ym);return *this;}

inline float GetXM()const noexcept{return xm;}
inline float GetYM()const noexcept{return ym;}
inline float GetW2()const noexcept{return w2;}
inline float GetH2()const noexcept{return h2;}
inline float GetAngle()const noexcept{return angle;}
};
class SSquircle
{
public: 
float x; float y; float a; float b; float angle; std::array<float,1026>vertices; 

inline void UpdateShape()noexcept
{
    vertices= TransformVertices<1026>(__FGE_PRIMITIVE_PRELOAD_SQUIRCLE_DATA, x,y,a,b,angle);
}
SSquircle(){}
SSquircle(float X, float Y, float A, float B,float ANGLE=0):x(X),y(Y),a(A),b(B),angle{ANGLE}{
    UpdateShape();
}
inline SSquircle& Draw()noexcept
{
    __FGE_PRIM_RENDER_FILL_SHAPE((float*)vertices.data(),513);
    return *this;
}
inline SSquircle& Draw(const FGE_Color& color)noexcept
{ 
    FGE_SetColor(color);
    return Draw();
}
inline SSquircle& DrawBorder()noexcept
{
    __FGE_PRIM_RENDER_DRAW_SHAPE((float*)vertices.data(),513);
    return *this;
}
inline SSquircle& DrawBorder(const FGE_Color& color)noexcept
{
    FGE_SetColor(color);
    return DrawBorder();
}
inline SSquircle& SetX(float X)noexcept{x=X;return *this;}
inline SSquircle& SetY(float Y)noexcept{y=Y;return *this;}
inline SSquircle& SetA(float A)noexcept{a=A;return *this;}
inline SSquircle& SetB(float B)noexcept{b=B;return *this;}
inline SSquircle& SetAngle(float ANGLE)noexcept{angle=ANGLE;return *this;}
inline SSquircle& ShiftX(float dx)noexcept{x+=dx;return *this;}
inline SSquircle& ShiftY(float dy)noexcept{y+=dy;return *this;}
inline SSquircle& Rotate(float dTheta)noexcept{angle+=dTheta;return *this;}
inline SSquircle& LERP(const FGE_FPoint& p, float lerpRate=0.01){x+=lerpRate*(p.x-x);y+=lerpRate*(p.y-y);return *this;}
inline SSquircle& SMOOTHSTEP(const FGE_FPoint& p, float stepRate=0.04){x+=SHAPE_SMOOTHSTEP(stepRate*QM::tanh(p.x-x))*(p.x-x);y+=SHAPE_SMOOTHSTEP(stepRate*QM::tanh(p.y-y))*(p.y-y);return *this;}

inline float GetX()const noexcept{return x;}
inline float GetY()const noexcept{return y;}
inline float GetA()const noexcept{return a;}
inline float GetB()const noexcept{return b;}
inline float GetAngle()const noexcept{return angle;}

};
class STriangle
{
public: 
FGE_FPoint a,b,c;
STriangle(){}
STriangle(const FGE_FPoint& A, const FGE_FPoint& B, const FGE_FPoint& C ):a(A),b(B),c(C){}
inline std::array<float,6> GetVertices()const noexcept
{
    return {a.x,a.y,b.x,b.y,c.x,c.y};
}

inline STriangle& Draw()noexcept
{
    __FGE_PRIM_RENDER_FILL_TRIANGLE((float*)this,3);
    return *this;
}
inline STriangle& DrawBorder()noexcept
{
    __FGE_PRIM_RENDER_DRAW_SHAPE((float*)this,3);
    return *this;
}
inline STriangle& DrawBorder(const FGE_Color& color)noexcept
{
    FGE_SetColor(color);
    return  DrawBorder();
}
inline STriangle& Draw(const FGE_Color& color)noexcept
{
    FGE_SetColor(color);
    return Draw();
}
inline STriangle& SetA(const FGE_FPoint& A)noexcept{a=A;return *this;}
inline STriangle& SetB(const FGE_FPoint& B)noexcept{b=B;return *this;}
inline STriangle& SetC(const FGE_FPoint& C)noexcept{c=C;return *this;}

inline FGE_FPoint GetA()const noexcept{return a;}
inline FGE_FPoint GetB()const noexcept{return b;}
inline FGE_FPoint GetC()const noexcept{return c;}
};
class SPlus
{
public: 
float x; float y; float l; std::array<float,26>vertices; 

SPlus(){}
inline void UpdateShape()noexcept
{
vertices=TransformVertices<26>(__FGE_PRIMITIVE_PRELOAD_PLUS_DATA,x,y,l,l);
}

SPlus(float X, float Y, float L):x(X),y(Y),l(L){
UpdateShape();

}
inline SPlus& Draw()noexcept
{
    __FGE_PRIM_RENDER_FILL_SHAPE((float*)vertices.data(),13);
    return *this;
}
inline SPlus& DrawBorder()noexcept
{
    __FGE_PRIM_RENDER_DRAW_SHAPE((float*)vertices.data(),13);
    return *this;
}
inline SPlus& DrawBorder(const FGE_Color& color)noexcept
{
    FGE_SetColor(color);
    return  DrawBorder();
}
inline SPlus& Draw(const FGE_Color& color)noexcept
{
    FGE_SetColor(color);
    return Draw();
}
inline SPlus& SetX(float X)noexcept{x=X;return *this;}
inline SPlus& SetY(float Y)noexcept{y=Y;return *this;}
inline SPlus& SetL(float L)noexcept{l=L;return *this;}
inline SPlus& ShiftX(float dx)noexcept{x+=dx;return *this;}
inline SPlus& ShiftY(float dy)noexcept{y+=dy;return *this;}
inline SPlus& LERP(const FGE_FPoint& p, float lerpRate=0.01){x+=lerpRate*(p.x-x);y+=lerpRate*(p.y-y);return *this;}
inline SPlus& SMOOTHSTEP(const FGE_FPoint& p, float stepRate=0.04){x+=SHAPE_SMOOTHSTEP(stepRate*QM::tanh(p.x-x))*(p.x-x);y+=SHAPE_SMOOTHSTEP(stepRate*QM::tanh(p.y-y))*(p.y-y);return *this;}

inline float GetX()const noexcept{return x;}
inline float GetY()const noexcept{return y;}
inline float GetL()const noexcept{return l;}
};

/*TODO:Fix the transition of first and last vertices*/
inline std::array<float,1026> __FGE_SRoundedRectGeneratePrimitives(const float d)
{
   std::array<float,1026>buffer={};
   constexpr size_t CIRCLE_QUARTER{256};
   
   const std::array<float,CIRCLE_QUARTER> quarter1=TransformVertices<CIRCLE_QUARTER>(__FGE_PRIMITIVE_PRELOAD_CIRCLE_DATA,1-d,1-d,d,d);
   const std::array<float,CIRCLE_QUARTER> quarter2=TransformVertices<CIRCLE_QUARTER>(__FGE_PRIMITIVE_PRELOAD_CIRCLE_DATA+CIRCLE_QUARTER,-(1-d),1-d,d,d);
   const std::array<float,CIRCLE_QUARTER> quarter3=TransformVertices<CIRCLE_QUARTER>(__FGE_PRIMITIVE_PRELOAD_CIRCLE_DATA+2*CIRCLE_QUARTER,-(1-d),-(1-d),d,d);
   const std::array<float,CIRCLE_QUARTER> quarter4=TransformVertices<CIRCLE_QUARTER>(__FGE_PRIMITIVE_PRELOAD_CIRCLE_DATA+3*CIRCLE_QUARTER,1-d,-(1-d),d,d);
   std::copy(quarter1.begin(), quarter1.end(), buffer.begin());
   std::copy(quarter2.begin(), quarter2.end(), buffer.begin()+CIRCLE_QUARTER);
   std::copy(quarter3.begin(), quarter3.end(), buffer.begin()+CIRCLE_QUARTER*2);
   std::copy(quarter4.begin(), quarter4.end(), buffer.begin()+CIRCLE_QUARTER*3);
   buffer.at(buffer.size()-2)=quarter1.at(0);
   buffer.at(buffer.size()-1)=quarter1.at(1);

   return buffer;
}

class SRoundedRect
{
public: 
float xm; float ym; float w2; float h2;float angle;
private: 
float d; 
public:
std::array<float,1026>vertices;
std::array<float,1026>primitive;

inline SRoundedRect& UpdateShape()noexcept
{
vertices=TransformVertices<1026>(primitive.data(),xm,ym,w2,h2,angle);

return *this;
}
SRoundedRect(){
   primitive= __FGE_SRoundedRectGeneratePrimitives(d);
}
SRoundedRect(float X_M, float Y_M, float W_HALF, float H_HALF, float ANGLE=0,float D=0):xm(X_M),ym(Y_M),w2(W_HALF),h2(H_HALF),angle(ANGLE),d(D){
   primitive= __FGE_SRoundedRectGeneratePrimitives(d);
UpdateShape();
}
inline SRoundedRect& Draw()noexcept 
{
    __FGE_PRIM_RENDER_FILL_SHAPE((float*)vertices.data(),vertices.size()/2);
    return *this;
}
inline void Draw()const noexcept 
{
    __FGE_PRIM_RENDER_FILL_SHAPE((float*)vertices.data(),vertices.size()/2);
}
inline SRoundedRect& SetRect(const FGE_FRect& RECT)
{
xm=RECT.x;
ym=RECT.y;
w2=RECT.w;
h2=RECT.h;
return *this;
}
inline SRoundedRect& Draw(const FGE_Color& color)noexcept
{
    FGE_SetColor(color);
    return Draw();
}
inline SRoundedRect& DrawBorder()noexcept
{
    __FGE_PRIM_RENDER_DRAW_SHAPE((float*)vertices.data(),vertices.size()/2);
    return *this;
}
inline SRoundedRect& DrawBorder(const FGE_Color& color)noexcept
{
    FGE_SetColor(color);
    return DrawBorder();
}
inline SRoundedRect& SetXM(float XM)noexcept{xm=XM; return*this;}
inline SRoundedRect& SetYM(float YM)noexcept{ym=YM; return*this;}
inline SRoundedRect& SetW2(float W2)noexcept{w2=W2; return*this;}
inline SRoundedRect& SetH2(float H2)noexcept{h2=H2; return*this;}
inline SRoundedRect& SetAngle(float ANGLE)noexcept{angle=ANGLE; return*this;}
inline SRoundedRect& SetD(float D)noexcept{d=D; 
   primitive= __FGE_SRoundedRectGeneratePrimitives(d);
return*this;}

inline SRoundedRect& ShiftX(float dx)noexcept{xm+=dx;return *this;}
inline SRoundedRect& ShiftY(float dy)noexcept{ym+=dy;return *this;}
inline SRoundedRect& Rotate(float dTheta)noexcept{angle+=dTheta;return *this;}
inline SRoundedRect& LERP(const FGE_FPoint& p, float lerpRate=0.01){xm+=lerpRate*(p.x-xm);ym+=lerpRate*(p.y-ym);return *this;}
inline SRoundedRect& SMOOTHSTEP(const FGE_FPoint& p, float stepRate=0.04){xm+=SHAPE_SMOOTHSTEP(stepRate*QM::tanh(p.x-xm))*(p.x-xm);ym+=SHAPE_SMOOTHSTEP(stepRate*QM::tanh(p.y-ym))*(p.y-ym);return *this;}

inline float GetXM()const noexcept{return xm;}
inline float GetYM()const noexcept{return ym;}
inline float GetW2()const noexcept{return w2;}
inline float GetH2()const noexcept{return h2;}
inline float GetAngle()const noexcept{return angle;}
inline float GetD()const noexcept{return d;}

};




}


#endif