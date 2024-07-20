#include <iostream>
#include "fge.h"

//This library can be super extended with any kind of SDL, SDL2, or OpenGL functionality 
int main(int argc, char** argv)
{
    BUILD_ALL_TARGETS;
    //Creating the window context
    FGE::Window wind= FGE_General_Init();

    FGE::SRoundedRect rrect{100,100,160,80,0,0.9};
            
    FGE_Loop_Start(wind);
  
    rrect.Rotate(0.01).UpdateShape().Draw(FGE::red).DrawBorder();
    FGE_Loop_End(wind);

    FGE_Return();
}