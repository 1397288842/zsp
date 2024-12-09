#include "service.h"

namespace commlib
{
	std::condition_variable& exit_cv()
	{
		static std::condition_variable cv;
		return cv;
	}

	std::mutex& exit_mtx()
	{
		 static std::mutex mtx;
		 return mtx;
	}

	Service::Service()
	{

	}

	Service::~Service()
	{

	}

	void Service::Start()
	{
		thread_ = std::thread(&Service::CreateThreadService, this);
	}

	void Service::CreateThreadService()
	{
		tid_ = std::this_thread::get_id();

		if (!Init())
		{
			return;
		}

		Run();

		std::unique_lock<std::mutex> lk(exit_mtx());
		std::notify_all_at_thread_exit(exit_cv(), std::move(lk));
	}

	void Service::RunInService(FuncService&& fn)
	{
		if (IsInServiceThread())
		{
			fn();
		}
		else
		{
			queue_.enqueue(fn);
		}
	}

	void Service::ExecAsyncTasks()
	{
		FuncService fn;
		while (queue_.try_dequeue(fn))
		{
			fn();
		}
	}

}


