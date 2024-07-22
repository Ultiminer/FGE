#include <iostream>
#include "fge.h"
#include "fge_image.h"




int main(int argc, char** argv)
{
    //Creating the window context
    FGE::Window wind= FGE_General_Init();
    //Create Image
    FGE_Texture img={"test.png"};FGE_FRect img_body{-50,-50,200,200};
    FGE::SRoundedRect rrect{100,100,160,80,0,0.9};
    
    FGE_Loop_Start(wind);
    const float dt=wind.GetDeltaTime();
    FGE_DrawImage(img_body,img);
    rrect.Rotate(0.001*dt).UpdateShape().Draw(FGE::red).DrawBorder();
   /* int x,y; 
    wind.GetCursor(x,y);
    std::cout<<"x:"<<x<<"y:"<<y<<std::endl;*/
    FGE_Loop_End(wind);
    

    FGE_Return();
}