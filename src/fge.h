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

#define BUILD_ALL_TARGETS remove("../build/main.o");remove("../build/glad.o");

using namespace FGE; 


inline enum class FGE_STATE{
EXCEPT_ERROR=-1,
EXIT,
RUN
}__fge_state;

inline void FGE_SetState(const FGE_STATE& state)noexcept
{   
    __fge_state=state; 
}
inline FGE_STATE FGE_GetState()noexcept
{   
    return __fge_state;  
}
inline FGE::Window FGE_General_Init()noexcept
{
    FGE::Window wind=FGE::Window();
     //Initializing FGE functionality
    FGE_INIT_RENDER_DEFAULT();
    FGE_RENDER_SMOOTH();
     /*Creating BLACKPINK tm xDDD*/
    FGE_SetClearColor(FGE::lightpink|FGE::black);
    FGE_UseAbsoluteCoords(wind.GetWidth(),wind.GetHeight());
    FGE_SetState(FGE_STATE::RUN);    
    return wind;
}
#define FGE_Loop_Start(__FGE_WINDOW_OBJ__)__FGE_WINDOW_OBJ__.Show();__FGE_WINDOW_OBJ__.PollEvents(); while(__FGE_WINDOW_OBJ__.IsRunning()>0&&__fge_state==FGE_STATE::RUN){__FGE_WINDOW_OBJ__.PollEvents(); FGE_START_RENDER();
#define FGE_Loop_End(__FGE_WINDOW_OBJ__)__FGE_WINDOW_OBJ__.Swap();}FGE_PRIM_RENDER_DELETE();FGE_SetState(FGE_STATE::EXIT);
#define FGE_Return()   return (int)FGE_GetState(); 

#endif