#ifndef __LOG_H__
#define __LOG_H__

#include "spdlog/spdlog.h"
#include "spdlog/async.h"
#include "spdlog/logger.h"
#include "spdlog/common.h"
#include "spdlog/fmt/fmt.h"
#include "spdlog/fmt/bundled/printf.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/hourly_file_sink.h"
#include "spdlog/sinks/msvc_sink.h"
#include "spdlog/sinks/stdout_sinks.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "string.h"

#define LOG_LEVEL_TRACE    spdlog::level::level_enum::trace
#define LOG_LEVEL_DEBUG    spdlog::level::level_enum::debug
#define LOG_LEVEL_INFO     spdlog::level::level_enum::info
#define LOG_LEVEL_WARN     spdlog::level::level_enum::warn
#define LOG_LEVEL_ERROR    spdlog::level::level_enum::err
#define LOG_LEVEL_FATAL    spdlog::level::level_enum::critical
#define LOG_LEVEL_CLOSE    spdlog::level::level_enum::off

using namespace std;
namespace commlib
{
	class GlobalLog 
	{
	public:
		GlobalLog() = default;
		~GlobalLog() = default;

		bool init_log(const string& path, int level)
		{
			try
			{
				std::vector<spdlog::sink_ptr> sinks;

				auto hourly_sink = std::make_shared<spdlog::sinks::hourly_file_sink_mt>(path);
				sinks.push_back(hourly_sink);

				auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
				sinks.push_back(console_sink);

				_logger = std::make_shared<spdlog::logger>("", sinks.begin(), sinks.end());
				spdlog::set_default_logger(_logger);

				spdlog::set_pattern("[%x %T.%e %t %^%l%$] %s(%#): %v");
				spdlog::flush_on(spdlog::level::warn);
				spdlog::set_level(spdlog::level::level_enum(level));
			}
			catch (const std::exception& e)
			{
				printf("init spdlog failed err:%s\n", e.what());
				return false;
			}
			return true;
		}

	private:
		std::shared_ptr<spdlog::logger> _logger;
	};
}

#define  LogTrace(fmt, ...)    spdlog::log({ __FILE__, __LINE__, __FUNCTION__ }, LOG_LEVEL_TRACE, fmt, ##__VA_ARGS__);
#define  LogDebug(fmt, ...)    spdlog::log({ __FILE__, __LINE__, __FUNCTION__ }, LOG_LEVEL_DEBUG, fmt, ##__VA_ARGS__);
#define  LogInfo(fmt, ...)    spdlog::log({ __FILE__, __LINE__, __FUNCTION__ }, LOG_LEVEL_INFO, fmt, ##__VA_ARGS__);
#define  LogWarn(fmt, ...)    spdlog::log({ __FILE__, __LINE__, __FUNCTION__ }, LOG_LEVEL_WARN, fmt, ##__VA_ARGS__);
#define  LogError(fmt, ...)    spdlog::log({ __FILE__, __LINE__, __FUNCTION__ }, LOG_LEVEL_ERROR, fmt, ##__VA_ARGS__);
#define  LogFatal(fmt, ...)    spdlog::log({ __FILE__, __LINE__, __FUNCTION__ }, LOG_LEVEL_FATAL, fmt, ##__VA_ARGS__);

#endif // __LOG_H__

