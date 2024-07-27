#include <iostream>
#include "fge.h"
#include "fge_image.h"
#include "fge_font.h"



int main(int argc, char** argv)
{
    //Creating the window context
    FGE::Window wind= FGE_General_Init();
    FGE_Texture consolas=FGE_GetFontTexture("Consolas", FONT_SIZE::pt60);

    FGE_Loop_Start(wind);
    //renders a label with yellowgreen color
    FGE_SetColor(FGE::yellowgreen);
    FGE_RenderText("Lets make a nice label xD",{-250,-50,500,40},18,40,consolas);
    FGE_Loop_End(wind);
    

    FGE_Return();
}