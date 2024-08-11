#define SRC_PATH "src/"

#include <iostream>
#include "src/fge.h"
/*
ALL calls are garded with fge_
*except* for using color you can include namespace fge 
-> using namespace fge; 
*/

int main(int argc, char** argv)
{
    
    fge_window wind= fge_general_init(); //Creating the window context
    fge_texture consolas=fge_get_font_texture("Consolas", FONT_SIZE::pt60); //Loading the consolas font into memory
    const size_t time_init=fge_current_milliseconds(); //calculate the time, when program starts

    fge_start(wind); //Initialize draw loop

    const float seconds=(fge_current_milliseconds()-time_init)/1000.f; //Calculate time passed in seconds
    fge_set_color(fge::chocolate); //Set Drawing color and render text to screen
    
    fge_render_text("Current time:"+std::to_string(seconds),  
    {-250,-50,500,40},18,40,
    consolas);
    
    fge_end(wind);//end draw loop
    
    
    fge_return();//return
}