#ifndef __NET_SERVICE_H__
#define __NET_SERVICE_H__

#include "evpp/tcp_callbacks.h"
#include "evpp/event_loop.h"
#include "evpp/tcp_server.h"
#include "evpp/tcp_client.h"
#include "evpp/slice.h"


#include "service.h"
#include "server_net.h"

namespace commlib
{
	class NetService : public Service
	{
	public:
		NetService();
		virtual ~NetService();

		void Run() override;
		bool Init() override;
	public:
		evpp::TCPServer* Listen(Service* srv, evpp::TCPHandler* h);

		void Stop();
	public:
		void OnMessage(Service* srv, evpp::TCPHandler* handler, const evpp::TCPConnPtr& conn, evpp::Buffer* msg);
		void OnAccept(const evpp::TCPConnPtr& conn);
		void OnClose(const evpp::TCPConnPtr& conn);

		void Send(uint64_t hd, evpp::Slice* buffer);
		void Close(uint64_t hd);
	private:
		void StopInLoop();

	private:
		std::mutex mutex_;
		evpp::EventLoop* loop_;
		std::unordered_map<string, evpp::TCPServer*> tcp_servers_;
		std::unordered_map<int, evpp::TCPClient*> tcp_clients_;
		std::unordered_map<uint64_t, evpp::TCPConnPtr> tcp_conns_;
	};
} // namespace commlib

#endif // __NET_SERVICE_H__
