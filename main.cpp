#define SRC_PATH "src/"

#include <iostream>
#include "src/fge.h"
#include "src/fge_image.h"
#include "src/fge_font.h"

using namespace fge; 



int main(int argc, char** argv)
{
    
    //Creating the window context
    fge_window wind= fge_general_init();
    fge_texture consolas=get_font_texture("Consolas", FONT_SIZE::pt60);

    const size_t time_init=fge_current_milliseconds();
    fge_loop_start(wind);

    set_color(chocolate);
    render_text("Current time:"+std::to_string((fge_current_milliseconds()-time_init)/1000.f),{-250,-50,500,40},18,40,consolas);
    fge_loop_end(wind);
    

    fge_return();
}