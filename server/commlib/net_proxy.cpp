#include "net_proxy.h"
#include "net_packet.h"

namespace commlib
{


	NetProxy::NetProxy()
	{

	}


	NetProxy::~NetProxy()
	{

	}

	void NetProxy::SendProto(const evpp::TCPConnPtr& conn, int cmd, char* data, int len)
    {
        std::lock_guard<std::mutex> guard(mutex_);

        //PkgHeader head{};
        //head.cmd = cmd;
        //head.length = len;
        //head.version = 10;
        //char head_str[PACKET_HEADER_SIZE] = {};
        //::memcpy(head_str, &head, PACKET_HEADER_SIZE);

        //evpp::Buffer buffer;
        //buffer.Append(head_str, PACKET_HEADER_SIZE);
        //buffer.Append(data, len);
        //conn->Send(&buffer);
    }

}