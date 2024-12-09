#ifndef __SERVICE_H__
#define __SERVICE_H__
#include "common.h"
#include "concurrentqueue/concurrentqueue.h"

namespace commlib
{
	class Service
	{
		using FuncService = std::function<void()>;
	public:
		Service();
		virtual ~Service();

		virtual void Start();
		virtual void Run() = 0;
		virtual bool Init() = 0;
	public:
		void CreateThreadService();
		void RunInService(FuncService&& fn);

		bool IsInServiceThread() const
		{
			return tid_ == std::this_thread::get_id();
		}

		std::thread::id& tid() {
			return tid_;
		}

		void ExecAsyncTasks();
	private:
		std::thread thread_;
		std::thread::id tid_;
		moodycamel::ConcurrentQueue<FuncService> queue_;
	};
}

#endif // ifndef __SERVICE_H__
