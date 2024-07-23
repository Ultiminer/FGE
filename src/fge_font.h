#ifndef FGE_FONT_H_
#define FGE_FONT_H_
#include "fge_debug.h"
#include <fstream>
#include "fge_image.h"



enum class FONT_SIZE
{
NONE, 
pt24, 
pt32,
pt40,
pt48,
pt56,
pt64
};
inline std::string __FONT_SIZE_TO_PATH_NAME(const FONT_SIZE& s)noexcept
{
    switch (s)
    {
        case FONT_SIZE::NONE: return "_0";
        case FONT_SIZE::pt24: return "_24";
        case FONT_SIZE::pt32: return "_32";
        case FONT_SIZE::pt40: return "_40";
        case FONT_SIZE::pt48: return "_48";
        case FONT_SIZE::pt56: return "_56";
        case FONT_SIZE::pt64: return "_64";
    }
}

inline FGE_Texture FGE_GetFontTexture(const std::string& name, const FONT_SIZE& pt)noexcept
{
    inline constexpr const char* path_head="../font/";
    inline constexpr const char* file_format=".png";
    const std::string path=path_head+name+"/"+name+__FONT_SIZE_TO_PATH_NAME(pt)+file_format;
    const FGE_Texture retVal=FGE_Texture(path.c_str());


    return retVal;
}
inline void FGE_RenderText(const std::string& txt,const FGE_DistRect& container, const FGE_DistRect& glyph, const FGE_Texture& text)noexcept
{
    const FGE_FRect border=container.get_padding_box();
    const FGE_FRect img_dim=glyph.get_padding_box();

    FGE_FRect img_wind={border.x+glyph.margin_left+glyph.padding_left,border.y+glyph.margin_bottom+glyph.padding_bottom, img_dim.w,img_dim.h};
    const float jump_x=img_dim.w+glyph.margin_left+glyph.margin_right+glyph.padding_right+glyph.padding_left;
    const float jump_y=img_dim.h+glyph.margin_top+glyph.margin_bottom+glyph.padding_top+glyph.padding_bottom; 

    
   /*
   
    UNDER CONSTRUCTION 
    DRAW FONTS HERE
   
   */

}




#endif