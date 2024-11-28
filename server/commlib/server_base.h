#ifndef ___SERVER_H__
#define ___SERVER_H__
#include "common.h"


namespace commlib
{
	class ServerBase
	{
	public:
		ServerBase() = default;
		virtual ~ServerBase() = default;
	public:
		virtual void Run() = 0;
	};
}

#endif // ___SERVER_H__

