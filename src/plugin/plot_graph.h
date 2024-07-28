#ifndef PLOT_GRAPH_H_
#define PLOT_GRAPH_H_
#include "fge.h"
#include "ext/quick_math.h"
#include <vector>
#include <functional>

struct CoordSys
{
float dim_x; 
float dim_y; 
float dim_w; 
float dim_h;
float scale_x; 
float scale_y; 
};

inline void FGE_DrawCoordSys(const CoordSys& sys,const FGE_Texture& img_font)noexcept
{
    {
    std::vector<FGE_FPoint> pts;
    const size_t half_w=0.5*sys.dim_w/sys.scale_x;
    for(size_t i=0; i<sys.dim_w/sys.scale_x; ++i)
    {
        pts.push_back({sys.dim_x+sys.scale_x*i, sys.dim_y});
        pts.push_back({sys.dim_x+sys.scale_x*i,sys.dim_y+sys.dim_h});

        FGE_RenderText(std::to_string((int)(i-half_w)),{sys.dim_x+sys.scale_x*i,sys.dim_y+sys.dim_h/2-sys.scale_y,sys.scale_x,sys.scale_y},sys.scale_x/3,sys.scale_y/3,img_font);
    }
     pts.push_back({sys.dim_x+sys.dim_w, sys.dim_y});
    pts.push_back({sys.dim_x+sys.dim_w,sys.dim_y+sys.dim_h});
    const size_t half_h=0.5*sys.dim_h/sys.scale_y;
    for(size_t i=1; i<=sys.dim_h/sys.scale_y; ++i)
    {
        pts.push_back({sys.dim_x          , sys.dim_y+sys.scale_y*i});
        pts.push_back({sys.dim_x+sys.dim_w, sys.dim_y+sys.scale_y*i});
        
        FGE_RenderText(std::to_string((int)(i-half_h)),{sys.dim_x+sys.dim_w/2,sys.dim_y+sys.scale_y*i-sys.scale_y,sys.scale_x,sys.scale_y},sys.scale_x/3,sys.scale_y/3,img_font);
    }
     pts.push_back({sys.dim_x          , sys.dim_y});
     pts.push_back({sys.dim_x+sys.dim_w, sys.dim_y});
    __FGE_PRIM_RENDER_DRAW_LINE((float*)pts.data(),pts.size());
    }
    {
    FGE_SetColor(FGE::black);
    const std::array<FGE_FPoint,4> pts{{{sys.dim_x+sys.dim_w/2, sys.dim_y},{sys.dim_x+sys.dim_w/2, sys.dim_y+sys.dim_h}
    ,{sys.dim_x, sys.dim_y+sys.dim_h/2},{sys.dim_x+sys.dim_w, sys.dim_y+sys.dim_h/2}
    }};
    __FGE_PRIM_RENDER_DRAW_LINE((float*)pts.data(),4);
    }

}

inline std::vector<FGE_FPoint> FGE_SampleFun(const std::function<float(float)>& fun, float a, float b, float epsilon, float scale_x=1, float scale_y=1)noexcept
{
    std::vector<FGE_FPoint> retVal; 
    for(float x=a; x<b; x+=epsilon)
    {
        retVal.push_back({x, fun(x/scale_x)*scale_y});
    }

    return retVal; 
}

struct FGE_GraphSystem
{
    float width; float height; float epsilon; float scale_x; float scale_y;
    std::vector<std::vector<FGE_FPoint>> graphs; 
    FGE_Texture consolas=FGE_GetFontTexture("Consolas",FONT_SIZE::pt75);

    inline void add_graph(const std::function<float(float)>&fun)noexcept
    {
        graphs.push_back(FGE_SampleFun(fun,-width/2,width/2,epsilon,scale_x,scale_y));
    }
    inline void draw()noexcept
    {
        FGE_SetColor(FGE::gray);
        FGE_DrawCoordSys({-width/2,-height/2,width,height,scale_x,scale_y},consolas);
        for(size_t i=0; i<graphs.size();++i){
       
            FGE_SetColor((i*53)%255, (i*53+11)%255,(255-i*37)%255,255);
        __FGE_PRIM_RENDER_DRAW_SHAPE((float*)graphs.at(i).data(),graphs.at(i).size());
        }
    }
};
inline FGE_GraphSystem FGE_CreateGraphSystem(float width, float height, float epsilon, float scale_x,float scale_y)
{
    return {width,height,epsilon,scale_x,scale_y};
}


#endif