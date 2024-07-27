#include <iostream>
#include "fge.h"
#include "fge_image.h"
#include "fge_font.h"



int main(int argc, char** argv)
{
    //Creating the window context
    FGE::Window wind= FGE_General_Init();
    
    FGE_Loop_Start(wind);
    FGE_RenderText("Hi Label World :))",{0,0,500,100},15,30,"Consolas",FONT_SIZE::pt30);

    FGE_Loop_End(wind);
    

    FGE_Return();
}