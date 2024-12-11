
#include "gateway_server.h"

#include "net_packet.h"
#include "app.h"
#include "comm_pre.h"
#include "net_service.h"

using namespace commlib;

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
		LogDebug("gateway server Run");
		while (true)
		{

			ExecAsyncTasks();
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	}


	bool Server::Init()
	{
		gSrvNet->Listen(this, this);
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
	

	void Server::OnConnect(const evpp::TCPConnPtr& conn)
	{
		LogInfo("conn success");
	}

	void Server::OnPacket(const evpp::TCPConnPtr& conn, commlib::NetPacket* pkt)
	{
		LogInfo("recv data");
	}


	void Server::Install(commlib::App* app)
	{
		app->Rigster([]() {
			gSrv = new Server();
			return gSrv;
		});
	}

}



