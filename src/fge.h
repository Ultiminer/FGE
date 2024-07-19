#ifndef FGE_SETUP_H_
#define FGE_SETUP_H_
#include "fge_window.h"
#include "fge_shape.h"
#include "fge_color.h"


#define BUILD_ALL_TARGETS remove("../build/main.o");remove("../build/glad.o");

using namespace FGE; 


inline enum class FGE_STATE{
ERROR=-1,
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
#define FGE_Loop_Start(__FGE_WINDOW_OBJ__) while(__FGE_WINDOW_OBJ__.IsRunning()&&__fge_state==FGE_STATE::RUN){FGE_START_RENDER();
#define FGE_Loop_End(__FGE_WINDOW_OBJ__)__FGE_WINDOW_OBJ__.Swap();__FGE_WINDOW_OBJ__.PollEvents();}FGE_PRIM_RENDER_DELETE();FGE_SetState(FGE_STATE::EXIT);
#define FGE_Return()   return (int)FGE_GetState(); 

#endif