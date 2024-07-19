#ifndef FGE_DEBUG_H_
#define FGE_DEBUG_H_

#include <iostream>


#ifdef FGE_Active
#define FGE_EXIT(msg) 
#else
#define FGE_EXIT(msg) {{std::cout<<msg<<std::endl; std::cout.flush(); exit(EXIT_FAILURE);}}

#endif





#endif