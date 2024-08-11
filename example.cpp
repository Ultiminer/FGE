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
    int wheel_pos=0,w=0,h=0;

    wind.get_screen(w,h);

    fge_start(wind); //Initialize draw loop
    wheel_pos+=wind.get_wheel_delta();

    fge_set_color(fge::chocolate); //Set Drawing color and render text to screen
    fge_render_text("Current wheel delta:"+std::to_string(wheel_pos),  
    {-250,-50,500,40},18,40,
    consolas);
    
    fge_end(wind);
    
    fge_return();//return
}