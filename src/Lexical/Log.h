#pragma once
#include<memory>
#include"Lexical/Core.h"
#include"spdlog/spdlog.h"
#include"spdlog/sinks/stdout_color_sinks.h"
#include"spdlog/fmt/ostr.h"
namespace Amc {

	class AMC_API Log
	{
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	public:
		static void init();
		inline static  std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static   std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	};

}

#define AMC_CORE_ERROR(...) ::Amc::Log::GetCoreLogger()->error(__VA_ARGS__)
#define AMC_CORE_WARN(...)  ::Amc::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define AMC_CORE_INFO(...)  ::Amc::Log::GetCoreLogger()->info(__VA_ARGS__)
#define AMC_CORE_TRACE(...) ::Amc::Log::GetCoreLogger()->trace(__VA_ARGS__)

#define AMC_CLIENT_ERROR(...) ::Amc::Log::GetClientLogger()->error(__VA_ARGS__)
#define AMC_CLIENT_WARN(...)  ::Amc::Log::GetClientLogger()->warn(__VA_ARGS__)
#define AMC_CLIENT_INFO(...)  ::Amc::Log::GetClientLogger()->info(__VA_ARGS__)
#define AMC_CLIENT_TRACE(...) ::Amc::Log::GetClientLogger()->trace(__VA_ARGS__)