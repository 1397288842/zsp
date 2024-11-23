#pragma once
#include "evpp/tcp_conn.h"
#include "packet.h"

namespace commlib
{
    class NetProxy
    {
    public:
        NetProxy() {};
        ~NetProxy() {};


    public:
        void SendProto(const evpp::TCPConnPtr& conn, int cmd, char* data, int len);
    private:
        std::mutex mutex_;

    public:
        Packet packet_;
    };
}