#ifndef __GATEWAY_SERVER_H__
#define __GATEWAY_SERVER_H__

#include "server_service.h"
#include "common.h"
#include "evpp/inner_pre.h"
#include "evpp/tcp_conn.h"

namespace commlib {
	class NetPacket;
	class App;
}

namespace gateway_server
{
	class Server : public commlib::ServerService, public evpp::TCPHandler
	{
	public:
		Server();
		~Server();


		void Run() override;
		bool Init() override;

		void OnAccept(const evpp::TCPConnPtr& conn) override;
		void OnClose(const evpp::TCPConnPtr& conn) override;
		void OnConnect(const evpp::TCPConnPtr& conn) override;
		void OnPacket(const evpp::TCPConnPtr& conn, commlib::NetPacket* pkt) override;
	public:
		static void Install(commlib::App* app);
	};
}


#endif // __GATEWAY_SERVER_H__

