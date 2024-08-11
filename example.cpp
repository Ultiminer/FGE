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
    
    //Creating the window context
    fge_window wind= fge_general_init();

    //Loading the consolas font into memory
    fge_texture consolas=fge_get_font_texture("Consolas", FONT_SIZE::pt60);

    //calculate the time, when program starts
    const size_t time_init=fge_current_milliseconds();

    //Initialize draw loop
    fge_start(wind);

    //Calculate time passed in seconds
    const float seconds=(fge_current_milliseconds()-time_init)/1000.f;

    //Set Drawing color and render text to screen
    fge_set_color(fge::chocolate);

    fge_render_text("Current time:"+std::to_string(seconds),
    {-250,-50,500,40},18,40,
    consolas);
    //end draw loop
    fge_end(wind);
    
    //return
    fge_return();
}