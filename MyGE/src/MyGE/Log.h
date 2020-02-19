#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog//fmt/ostr.h"


namespace MyGE {

    class MYGE_API Log
    {
        // Methods
        public:
            static void Init();

            inline static std::shared_ptr<spdlog::logger>& GetCoreLogger()      { return s_CoreLogger; }
            inline static std::shared_ptr<spdlog::logger>& GetClientLogger()    { return s_ClientLogger; }

        // Variables
        private:
            static std::shared_ptr<spdlog::logger> s_CoreLogger;
            static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };

}

// Core log macros
#define MG_CORE_TRACE(...)      ::MyGE::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define MG_CORE_INFO(...)       ::MyGE::Log::GetCoreLogger()->info(__VA_ARGS__)
#define MG_CORE_WARN(...)       ::MyGE::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define MG_CORE_ERROR(...)      ::MyGE::Log::GetCoreLogger()->error(__VA_ARGS__)
#define MG_CORE_CRITICAL(...)   ::MyGE::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define MG_TRACE(...)           ::MyGE::Log::GetClientLogger()->trace(__VA_ARGS__)
#define MG_INFO(...)            ::MyGE::Log::GetClientLogger()->info(__VA_ARGS__)
#define MG_WARN(...)            ::MyGE::Log::GetClientLogger()->warn(__VA_ARGS__)
#define MG_ERROR(...)           ::MyGE::Log::GetClientLogger()->error(__VA_ARGS__)
#define MG_CRITICAL(...)        ::MyGE::Log::GetClientLogger()->critical(__VA_ARGS__)