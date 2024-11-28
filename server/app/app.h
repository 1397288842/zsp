#ifndef __APP_H__
#define __APP_H__

#include "common.h"
#include "server_base.h"

class App
{
public:
	App();
	~App();
	void Run();
	void Start();
	void Rigster(commlib::ServerBase* srv);

private:
	std::list<commlib::ServerBase*> srvs_;
	std::thread thread_;
};

#endif // __APP_H__
