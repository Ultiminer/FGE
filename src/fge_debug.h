#ifndef FGE_DEBUG_H_
#define FGE_DEBUG_H_

#include <iostream>
#define fge_print(x) std::cout<<x<<"\n"<<std::flush;
#define fge_range(param, MAX_VAL) for(size_t (param) =0; (param)<(MAX_VAL);++(param))


inline std::string fge_input(const char* const msg)noexcept
{
fge_print(msg);
std::string line="";
std::getline(std::cin,line);
return line;
}

constexpr inline void fge_fun_assert(bool eval, const char* const expr, const char* const file, const size_t line )noexcept
{
    if(eval)return; 
    std::cout<< "assert condition: "<< expr<<" failed :( \n"<<file<<" at line: " <<line<<"\n"<<std::flush;
    if(fge_input("To exit ONLY press ENTER:")!="")return;
    exit(EXIT_FAILURE);
}


#ifdef FGE_Active
#define FGE_EXIT(msg) 
#define fge_assert(expr) (expr)

#else
#define FGE_EXIT(msg) {{std::cout<<msg<<std::endl; std::cout.flush(); exit(EXIT_FAILURE);}}
#define fge_assert(expr) fge_fun_assert((expr),#expr,__FILE__,__LINE__)

#endif




#endif