#pragma once

#ifdef MG_PLATFORM_WINDOWS
    #if MG_DYNAMIC_LINK
        #ifdef MG_BUILD_DLL
            #define MYGE_API __declspec(dllexport)
        #else
            #define MYGE_API __declspec(dllimport)
        #endif
    #else
        #define MYGE_API
    #endif
#else
    #error MyGE only supports Windows
#endif // MG_PLATFORM_WINDOWS

#ifdef MG_DEBUG
    #define MG_ENABLE_ASSERTS
#endif // MG_DEBUG


#ifdef MG_ENABLE_ASSERTS
    #define MG_ASSERT(x, ...) {if(!(x)) {MG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
    #define MG_CORE_ASSERT(x, ...) {if(!(x)) {MG_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
    #define MG_ASSERT(x, ...)
    #define MG_CORE_ASSERT(x, ...)
#endif

#define BITT(x) (1 << x)

#define MG_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)