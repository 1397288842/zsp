#include "evpp/inner_pre.h"

#include "evpp/listener.h"
#include "evpp/event_loop.h"
#include "evpp/fd_channel.h"
#include "evpp/libevent.h"
#include "evpp/sockets.h"

#ifdef H_OS_WINDOWS
// avoid compiling failed because of 'errno' redefined as 'WSAGetLastError()'
#define errno WSAGetLastError()
#endif

namespace evpp
{
Listener::Listener(EventLoop* l, const std::string& addr)
    : loop_(l), addr_(addr)
{
}

Listener::~Listener()
{
    //LogInfo("~Listener fd:{}", chan_->fd());
    chan_.reset();
    EVUTIL_CLOSESOCKET(fd_);
    fd_ = INVALID_SOCKET;
}

void Listener::Listen(int backlog)
{
    LogInfo("server listen start addr:{}", addr_);
    fd_ = sock::CreateNonblockingSocket();
    if (fd_ < 0)
    {
        int serrno = errno;
        LogFatal("Create a nonblocking socket failed:{}", strerror(serrno));
        return;
    }

    struct sockaddr_storage addr = sock::ParseFromIPPort(addr_.data());
    // TODO Add retry when failed
    int ret = ::bind(fd_, sock::sockaddr_cast(&addr), static_cast<socklen_t>(sizeof(struct sockaddr)));
    if (ret < 0)
    {
        int serrno = errno;
        LogFatal("bind error:{} addr:{}", strerror(serrno), addr_);
        return;
    }

    ret = ::listen(fd_, backlog);
    if (ret < 0)
    {
        int serrno = errno;
        LogFatal("Listen failed:{}", strerror(serrno));
        return;
    }

    LogInfo("server listen at addr:{} success", addr_);
}

void Listener::Accept()
{
    chan_.reset(new FdChannel(loop_, fd_, true, false));
    chan_->SetReadCallback(std::bind(&Listener::HandleAccept, this));
    loop_->RunInLoop(std::bind(&FdChannel::AttachToLoop, chan_.get()));
    LogInfo("TCPServer is running");
}

void Listener::HandleAccept()
{
    LogInfo("A new connection is comming in");
    assert(loop_->IsInLoopThread());
    struct sockaddr_storage ss;
    socklen_t addrlen = sizeof(ss);
    int nfd = -1;
    if ((nfd = ::accept(fd_, sock::sockaddr_cast(&ss), &addrlen)) == -1)
    {
        int serrno = errno;
        if (serrno != EAGAIN && serrno != EINTR)
        {
            LogError("bad accept:{}", strerror(serrno));
        }
        return;
    }

    if (evutil_make_socket_nonblocking(nfd) < 0)
    {
        LogError("set fd:{} nonblocking failed.", nfd);
        EVUTIL_CLOSESOCKET(nfd);
        return;
    }

    sock::SetKeepAlive(nfd, true);

    std::string raddr = sock::ToIPPort(&ss);
    if (raddr.empty())
    {
        LogError("sock::ToIPPort(&ss) failed.");
        EVUTIL_CLOSESOCKET(nfd);
        return;
    }

    LogInfo("accepted a connection from:{} listen fd:{} client fd:{}", raddr, fd_, nfd);
    if (new_conn_fn_)
    {
        new_conn_fn_(nfd, raddr, sock::sockaddr_in_cast(&ss));
    }
}

void Listener::Stop()
{
    assert(loop_->IsInLoopThread());
    chan_->DisableAllEvent();
    chan_->Close();
}
}
