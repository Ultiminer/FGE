#define SRC_PATH "src/"

#include <iostream>
#include "src/fge.h"
#include "src/fge_image.h"
#include "src/fge_font.h"




int main(int argc, char** argv)
{
    
    //Creating the window context
    fge_window wind= fge_general_init();
    //Loading the consolas font into memory
    fge_texture consolas=fge::get_font_texture("Consolas", FONT_SIZE::pt60);

    const size_t time_init=fge_current_milliseconds();

    //Initialize game loop
    fge_start(wind);

    //Set Drawing color and render text to screen
    fge::set_color(fge::chocolate);
    fge::render_text("Current time:"+std::to_string((fge_current_milliseconds()-time_init)/1000.f),
    {-250,-50,500,40},18,40,
    consolas);
    
    //end draw loop
    fge_end(wind);
    
    //return
    fge_return();
}