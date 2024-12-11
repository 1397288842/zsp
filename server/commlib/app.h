#ifndef __APP_H__
#define __APP_H__

#include "common.h"
#include "service.h"

namespace commlib
{
	class App
	{
	public:
		using FuncService = std::function<Service*()>;
		App();
		~App();
		void Run();
		void Start();
		void Rigster(FuncService&& func);

	private:
		void AddService(Service* srv);

	private:
		std::list<FuncService> nodes_;
		std::list<Service*> srvs_;
	};
}


#endif // __APP_H__
