#ifndef ___SERVER_H__
#define ___SERVER_H__
#include "common.h"
#include "service.h"

namespace commlib
{
	class ServerService: public Service
	{
	public:
		ServerService() {}
		virtual ~ServerService() {}
	public:
		void Run() override {};
	};
}

#endif // ___SERVER_H__

