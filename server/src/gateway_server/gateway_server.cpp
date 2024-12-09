
#include "gateway_server.h"

#include "net_packet.h"

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

			ExecAsyncTasks();
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	}


	bool Server::Init()
	{
		return true;
	}

	void Server::OnAccept(const evpp::TCPConnPtr& conn)
	{
		conn->set_context(evpp::Any(commlib::PackType::PT_CLIENT));
		LogInfo("accept new conn");
	}


	void Server::OnClose(const evpp::TCPConnPtr& conn)
	{
		LogInfo("close conn");
	}
	

	void Server::OnPacket(const evpp::TCPConnPtr& conn, commlib::NetPacket* pkt)
	{
		LogInfo("recv data");
	}

}



