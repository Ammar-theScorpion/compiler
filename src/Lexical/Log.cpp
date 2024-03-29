#include "amcpch.h"
#include "Log.h"

namespace Amc {
    std::shared_ptr<spdlog::logger>Log::s_ClientLogger;
    std::shared_ptr<spdlog::logger>Log::s_CoreLogger;

    void Log::init()
    {
        spdlog::set_pattern("%^ %n : %v%$");
        s_CoreLogger = spdlog::stdout_color_mt("AMC");
        s_CoreLogger->set_level(spdlog::level::trace);

        s_ClientLogger = spdlog::stdout_color_mt("APP");
        s_ClientLogger->set_level(spdlog::level::trace);
    }
}
