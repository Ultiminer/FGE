#include <iostream>
#include "math.h"
#include "fge_setup.h"
#include "fge_image.h"
#include "fge_font.h"

//This library can be super extended with any kind of SDL, SDL2, or OpenGL functionality 
int FGE_Main()
{
    BUILD_ALL_TARGETS;
    //Creating the window context
    FGE::Window wind= FGE_General_Init();
    FGE::SRect rect={0,0,100,100};
    FGE_Texture text="test.png";
    FGE::SRoundedRect rrect{100,100,160,80,0,0.9};
    FGE::Label label={{0,0,400,100},"Hi Label World",FGE::LabelStd}; 
    FGE_Loop_Start(wind);
    FGE_DrawImage(rect,text);
    rect.Rotate(0.01).UpdateShape();
    rrect.Rotate(0.01).UpdateShape().Draw(FGE::red).DrawBorder();
    label.Draw();

    FGE_Loop_End(wind);

    FGE_Return();
}