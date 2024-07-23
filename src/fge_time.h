#ifndef FGE_CURRENT_MILLISECONDS_H_
#define FGE_CURRENT_MILLISECONDS_H_
#include <chrono>

inline size_t FGE_CurrentMilliseconds()noexcept{
return std::chrono::duration_cast< std::chrono::milliseconds >(
    std::chrono::system_clock::now().time_since_epoch()
).count();
}

#endif