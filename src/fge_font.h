#ifndef FGE_FONT_H_
#define FGE_FONT_H_
#include "fge_debug.h"
#include <fstream>
#include "fge_image.h"
#include <unordered_map>
/*
Library for loading monospaced fonts from images
*/
inline constexpr double FGE_FONTPOS_MULTIPLIER{1.0/95.0};
inline constexpr double FGE_FONTPOS_H{0.25};
inline constexpr double FGE_FONTPOS_Y_BOLD_ITALIC{0.0};
inline constexpr double FGE_FONTPOS_Y_ITALIC{FGE_FONTPOS_H};
inline constexpr double FGE_FONTPOS_Y_BOLD{FGE_FONTPOS_H*2};
inline constexpr double FGE_FONTPOS_Y_NORM{FGE_FONTPOS_H*3};

enum class FONT_SIZE
{
NONE, 
pt30,
pt45,
pt60,
pt75
};
inline std::string __FONT_SIZE_TO_PATH_NAME(const FONT_SIZE& s)noexcept
{
    switch (s)
    {
        case FONT_SIZE::pt30: return "_30";
        case FONT_SIZE::pt45: return "_45";
        case FONT_SIZE::pt60: return "_60";
        case FONT_SIZE::pt75: return "_75";
    }

    return "";
}
inline fge_texture fge_get_font_texture(const std::string& font_name, const FONT_SIZE& pt)noexcept
{
    const std::string src=__SRC_PATH;
    constexpr const char* path_head="../font/";
    constexpr const char* file_format=".png";
    const std::string path=src+path_head+font_name+__FONT_SIZE_TO_PATH_NAME(pt)+file_format;

    fge_texture retVal{path.c_str()};
    return retVal;
}
inline void fge_render_text(const std::string& txt,const fge_frect& label, float char_width, float char_height, const fge_texture& img)noexcept
{
    fge_frect dim={label.x,label.y+label.h-char_height, char_width, char_height};

    for(auto& ch: txt)
    {   
        //Check for collisions with label
        if(dim.x>label.x+label.w|| ch=='\n'){
            dim.x=label.x;
            dim.y-=char_height;
        }
        if(dim.y<label.y)return; 
        if(ch=='\n')continue;
        //Draw to screen if not bad character
        if(ch>32&&ch<177)
        fge_draw_alpha(dim,img,FGE_FONTPOS_MULTIPLIER,FGE_FONTPOS_H,1.009f*(ch-33)*FGE_FONTPOS_MULTIPLIER,FGE_FONTPOS_Y_NORM);
        
        //Advance character pointer
        dim.x+=char_width;
    }

}

inline void fge_render_text(const std::string& txt,const fge_frect& label, float char_width, float char_height, const std::string& font_name, const FONT_SIZE& pt)noexcept
{
    fge_texture img{fge_get_font_texture(font_name, pt)};
    fge_render_text( txt,label,  char_width,  char_height, img );
}


#endif