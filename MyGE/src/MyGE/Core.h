#pragma once

#ifdef MG_PLATFORM_WINDOWS
    #ifdef MG_BUILD_DLL
        #define MYGE_API __declspec(dllexport)
    #else
        #define MYGE_API __declspec(dllimport)
    #endif
#else
    #error MyGE only supports Windows
#endif // MG_PLATFORM_WINDOWS
