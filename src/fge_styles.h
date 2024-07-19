#ifndef FGE_STYLES_H_
#define FGE_STYLES_H_
#include "fge_color.h"
namespace FGE{
struct LabelStyle{
    float padding; 
    FGE_Color inside; 
    FGE_Color outside;
};
#define __FGE_CLabel inline constexpr LabelStyle

__FGE_CLabel LabelStd{7,FGE::darkgray,FGE::lightgray};
__FGE_CLabel LabelAlert{8,FGE::red,FGE::orange};
__FGE_CLabel LabelStdPro{7,FGE::gray,FGE::whitesmoke};
__FGE_CLabel LabelContrast{7,FGE::white,FGE::black};



}
#endif