#include "app.h"
#include "net_service.h"
#include "comm_pre.h"
//#include "log.hpp"

namespace commlib
{
	//GlobalLog* g_log = nullptr;
	//void InitGlobalLog()
	//{
	//	g_log = new GlobalLog();
	//}

	//void DestroyGlobalLog()
	//{
	//	SafeDelete(g_log);
	//}

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
		gSrvNet = new NetService();
		AddService(gSrvNet);

		// 初始化日志
		g_log->init_log("./testt.log", 1);

		for (auto& it:nodes_)
		{
			 auto service = it();
			 AddService(service);
		}

		for (auto *it:srvs_)
		{
			it->Start();
		}
	}

	void App::Rigster(FuncService&& func)
	{
		nodes_.push_back(func);
	}

	void App::AddService(Service* srv)
	{
		srvs_.push_back(srv);
	}

}





