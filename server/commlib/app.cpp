#include "app.h"
#include "server_service.h"

namespace commlib
{
	GlobalLog* g_log = nullptr;
	static void InitGlobalLog()
	{
		g_log = new GlobalLog();
	}

	static void DestroyGlobalLog()
	{
		delete g_log;
		g_log = nullptr;
	}

	extern std::condition_variable& exit_cv();
	extern std::mutex& exit_mtx();

	App::App()
	{
		InitGlobalLog();
	}

	App::~App()
	{
		DestroyGlobalLog();
	}

	void App::Run()
	{
		while (true)
		{
			std::unique_lock<std::mutex> lock(exit_mtx());
			exit_cv().wait(lock);

			for (auto* it : srvs_)
			{
				LogInfo("App quit");
			}
		}
	}

	void App::Start()
	{
		// 初始化日志
		g_log->init_log("./testt.log", 1);

		for (auto *it:srvs_)
		{
			it->Start();
		}
	}


	void App::Rigster(commlib::ServerService* srv)
	{
		srvs_.push_back(srv);
	}
}





