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
inline FGE_Texture FGE_GetFontTexture(const std::string& font_name, const FONT_SIZE& pt)noexcept
{
    constexpr const char* path_head="../font/";
    constexpr const char* file_format=".png";
    const std::string path=path_head+font_name+__FONT_SIZE_TO_PATH_NAME(pt)+file_format;

    FGE_Texture retVal{path.c_str()};
    return retVal;
}
inline void FGE_RenderText(const std::string& txt,const FGE_FRect& label, float char_width, float char_height, const std::string& font_name, const FONT_SIZE& pt)noexcept
{
    FGE_Texture img{FGE_GetFontTexture(font_name, pt)};

    FGE_FRect dim={label.x,label.h-char_height, char_width, char_height};

    for(auto& ch: txt)
    {   
        //Check for collisions with label
        if(dim.x>label.x+label.w|| ch=='\n'){
            dim.x=label.x;
            dim.y-=label.h;
        }
        if(dim.y<label.y)return; 
        if(ch=='\n')continue;

        //Draw to screen if not bad character
        if(ch>32&&ch<177)
        FGE_DrawImage(dim,img,FGE_FONTPOS_MULTIPLIER,FGE_FONTPOS_H,1.009f*(ch-33)*FGE_FONTPOS_MULTIPLIER,FGE_FONTPOS_Y_NORM);

        //Advance character pointer
        dim.x+=char_width;
    }

}




#endif