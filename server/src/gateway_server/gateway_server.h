#ifndef __GATEWAY_SERVER_H__
#define __GATEWAY_SERVER_H__

#include "server_base.h"
#include "common.h"
#include "evpp/inner_pre.h"
#include "evpp/tcp_conn.h"

using namespace commlib;

namespace gateway_server
{
	class Server : public ServerBase
	{
	public:
		Server();
		~Server();


		void Run() override;

		void OnAccept(const evpp::TCPConnPtr* conn);
		void OnClose(const evpp::TCPConnPtr& conn);
		void OnMessage(const evpp::TCPConnPtr& conn, const char* data, int len);
	public:
	};
}


#endif // __GATEWAY_SERVER_H__

