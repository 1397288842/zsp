#ifndef __COMM_PRE_H__
#define __COMM_PRE_H__

namespace commlib
{
	class NetService;
	class GlobalLog;




	void InitGlobalLog();
	void DestroyGlobalLog();

	extern GlobalLog* g_log;
	extern NetService* gSrvNet;
}

#endif // __COMM_PRE_H__


