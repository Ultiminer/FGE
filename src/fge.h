#ifndef FGE_SETUP_H_
#define FGE_SETUP_H_
#include "fge_window.h"
#include "fge_shape.h"
#include "fge_color.h"
/*
BSD 3-Clause License

Copyright (c) 2024, FloDev

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


inline enum class fge_state{
EXCEPT_ERROR=EXIT_FAILURE,
EXIT=EXIT_SUCCESS,
RUN
}__fge_state;

inline void fge_set_state(const fge_state& state)noexcept
{   
    __fge_state=state; 
}
inline fge_state fge_get_state()noexcept
{   
    return __fge_state;  
}
inline fge_window fge_general_init()noexcept
{
    fge_window wind=fge_window();
     //Initializing FGE functionality
    fge::init_render_default();
    fge::render_smooth();
    fge::set_clear_color(fge::lightpink|fge::black);
    fge::send_window_size(wind.get_width(),wind.get_height());
    fge::use_absolute_coords();
    fge_set_state(fge_state::RUN);    
    return wind;
}
#define fge_loop_start(__FGE_WINDOW_OBJ__)__FGE_WINDOW_OBJ__.show();__FGE_WINDOW_OBJ__.poll_events(); while(__FGE_WINDOW_OBJ__.is_running()>0&&__fge_state==fge_state::RUN){__FGE_WINDOW_OBJ__.poll_events(); FGE_START_RENDER();
#define fge_loop_end(__FGE_WINDOW_OBJ__)__FGE_WINDOW_OBJ__.swap();}FGE_PRIM_RENDER_DELETE();fge_set_state(fge_state::EXIT);
#define fge_return()   return (int)fge_get_state(); 

#endif