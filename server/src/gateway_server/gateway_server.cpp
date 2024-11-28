
#include "gateway_server.h"


namespace gateway_server
{
	Server* gSrv = nullptr;
	Server::Server()
	{
		LogDebug("gateway server construct");
	}

	Server::~Server()
	{

	}

	void Server::Run()
	{
		while (true)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	}

	void Server::OnAccept(const evpp::TCPConnPtr* conn)
	{

	}


	void Server::OnClose(const evpp::TCPConnPtr& conn)
	{

	}


	void Server::OnMessage(const evpp::TCPConnPtr& conn, const char* data, int len)
	{

	}

}



