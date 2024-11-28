#ifndef __STOP_WATCH_H__
#define __STOP_WATCH_H__

#include <chrono>
#include "common.h"

namespace commlib
{
	class StopWatch final
	{
	public:
		StopWatch() {
			start_ = std::chrono::system_clock::now();
		}
		~StopWatch() = default;

		// 统计耗时 单位：毫秒(ms)
		uint64_t Elapsed() const
		{
			auto end = std::chrono::system_clock::now();
			return std::chrono::duration_cast<std::chrono::milliseconds>(end - start_).count();
		}

		// 统计耗时 单位：微秒(us)
		uint64_t UElapsed() const
		{
			auto end = std::chrono::system_clock::now();
			return std::chrono::duration_cast<std::chrono::microseconds>(end - start_).count();
		}
	private:
		std::chrono::system_clock::time_point start_{};
	};
}

#endif // __STOP_WATCH_H__

