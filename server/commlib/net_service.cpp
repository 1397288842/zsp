#include "net_service.h"

#include "evpp/inner_pre.h"
#include "evpp/tcp_conn.h"
#include "evpp/buffer.h"

#include "log.hpp"
#include "net_packet.h"

namespace commlib
{
	NetService::NetService()
	{
		loop_ = new evpp::EventLoop();
	}

	NetService::~NetService()
	{
		SafeDelete(loop_);

		for (auto &it : tcp_servers_)
		{
			SafeDelete(it.second);
		}
	}

	void NetService::Run()
	{
		loop_->Run();
	}

	bool NetService::Init()
	{
		return true;
	}

	evpp::TCPServer* NetService::Listen(Service* srv, evpp::TCPHandler* h)
	{
		std::string addr = "0.0.0.0:9099";
		int thread_num = 4;
		auto* server = new evpp::TCPServer(loop_, addr, "TCPEchoServer", thread_num);
		server->SetMessageCallback([this, srv, h](const evpp::TCPConnPtr& conn, evpp::Buffer* msg) {
				OnMessage(srv, h, conn, msg);
			});
		server->SetConnectionCallback([this, srv, h](const evpp::TCPConnPtr& conn){
				if (conn->IsConnected())
				{
					OnAccept(srv, h, conn);
				}
				else
				{
					OnClose(conn);
				}
			});
		server->Init();
		server->Start();

		tcp_servers_.emplace(addr, server);
		return server;
	}

	void NetService::Stop()
	{
		StopInLoop();
	}

	void NetService::OnMessage(Service* srv, evpp::TCPHandler* handler, const evpp::TCPConnPtr& conn, evpp::Buffer* msg)
	{
		LogDebug("Receive a message len:{}", msg->length());

		auto type = conn->context().Get<PackType>();

		NetPacket pkg{};
		pkg.SetType(type);
		pkg.ReadBuffer(msg);

		srv->RunInService([this, srv, handler, conn, pkg{ std::move(pkg) }]() mutable {
			LogDebug("read msg is : {}", pkg.GetMsg().data());
			handler->OnPacket(conn, &pkg);
		});

	}

	void NetService::OnAccept(Service* srv, evpp::TCPHandler* handler, const evpp::TCPConnPtr& conn)
	{
		LogInfo("A new connection from:{} ", conn->remote_addr());
		tcp_conns_.emplace(conn->id(), conn);
		srv->RunInService([this, srv, handler, conn ]() {
			handler->OnAccept(conn);
		});
	}

	void NetService::OnClose(const evpp::TCPConnPtr& conn)
	{
		LogInfo("close by remote peer:{}  ", conn->remote_addr());
	}

	void NetService::Send(uint64_t hd, evpp::Slice* buffer)
	{
		std::lock_guard<mutex> lock(mutex_);
		auto it = tcp_conns_.find(hd);
		if (it != tcp_conns_.end())
		{
			it->second->Send(*buffer);
		}
	}

	void NetService::Close(uint64_t hd)
	{
		std::lock_guard<mutex> lock(mutex_);
		tcp_conns_.erase(hd);
	}

	void NetService::StopInLoop()
	{
		if (tcp_servers_.size() > 0)
		{
			for (auto& it : tcp_servers_)
			{
				if (it.second)
				{
					it.second->Stop([this]() {
							loop_->Stop();
						});
				}
			}
		}
		else
		{
			loop_->Stop();
		}
	}

}


