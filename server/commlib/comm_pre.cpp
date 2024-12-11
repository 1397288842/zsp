#include "comm_pre.h"
#include "log.hpp"
#include "macros.h"

namespace commlib {
	NetService* gSrvNet = nullptr;
	GlobalLog* g_log = nullptr;

	void InitGlobalLog()
	{
		g_log = new GlobalLog();
	}

	void DestroyGlobalLog()
	{
		SafeDelete(g_log);
	}
}