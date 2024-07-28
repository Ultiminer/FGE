#include <iostream>
#include "fge.h"
#include "fge_image.h"
#include "fge_font.h"



int main(int argc, char** argv)
{
    //Creating the window context
    FGE::Window wind= FGE_General_Init();
    FGE_Texture consolas=FGE_GetFontTexture("Consolas", FONT_SIZE::pt60);

    const size_t time_init=FGE_CurrentMilliseconds();
    FGE_Loop_Start(wind);

    FGE_SetColor(FGE::chocolate);
    FGE_RenderText("Current time:"+std::to_string((FGE_CurrentMilliseconds()-time_init)/1000.f),{-250,-50,500,40},18,40,consolas);
    FGE_Loop_End(wind);
    

    FGE_Return();
}