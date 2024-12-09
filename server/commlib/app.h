#ifndef __APP_H__
#define __APP_H__

#include "common.h"

namespace commlib
{
	class ServerService;
	class App
	{
	public:
		App();
		~App();
		void Run();
		void Start();
		void Rigster(commlib::ServerService* srv);

	private:
		std::list<commlib::ServerService*> srvs_;
	};
}


#endif // __APP_H__
