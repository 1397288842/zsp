#ifndef __NET_PROXY_H__
#define __NET_PROXY_H__

//#include "common.h"
#include "evpp/tcp_conn.h"
#include "net_packet.h"
#include "net_service.h"

namespace commlib
{
	class NetProxy
	{
	public:
		NetProxy(NetService* srv);
		~NetProxy();


	public:
		void SendProto(const evpp::TCPConnPtr& conn, int cmd, char* data, int len);
		void SendProto(uint64_t hd, int cmd, char* data, int len);
	public:
		NetPacket packet_;
	private:
		NetService* srv_net_;
	};
}

#endif // __NET_PROXY_H__

