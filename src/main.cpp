#include <iostream>
#include "fge.h"
#include "fge_image.h"
//This library can be super extended with any kind of SDL, SDL2, or OpenGL functionality 
int main(int argc, char** argv)
{
    BUILD_ALL_TARGETS;
    //Creating the window context
    FGE::Window wind= FGE_General_Init();
    //Create Image
    FGE_Texture img={"test.png"};FGE_FRect img_body{-50,-50,-200,-200};
    FGE::SRoundedRect rrect{100,100,160,80,0,0.9};
    
    FGE_Loop_Start(wind);

    FGE_DrawImage(img_body,img);
    rrect.Rotate(0.01).UpdateShape().Draw(FGE::red).DrawBorder();
    FGE_Loop_End(wind);

    FGE_Return();
}