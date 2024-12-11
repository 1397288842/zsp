// client_server.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "comm_pre.h"
#include "log.hpp"
#include <iostream>

#ifdef _WIN32
#include <Windows.h>
#ifdef _DEBUG
#include <tchar.h>
#include <DbgHelp.h>
#pragma comment(lib, "dbghelp.lib")
#endif // _DEBUG
#endif // _WIN32

#include <evpp/tcp_client.h>
#include <evpp/buffer.h>
#include <evpp/tcp_conn.h>

#include "net_proxy.h"

auto gLog = std::make_shared<commlib::GlobalLog>();
#ifdef _WIN32
#ifdef _DEBUG
LONG MinidumpCrashHandler(EXCEPTION_POINTERS* pException)
{
    TCHAR szDumpDir[MAX_PATH] = { 0 };
    TCHAR szDumpFile[MAX_PATH] = { 0 };
    TCHAR szMsg[MAX_PATH] = { 0 };
    SYSTEMTIME  stTime = { 0 };

    // 构建dump文件路径
    GetLocalTime(&stTime);
    ::GetCurrentDirectory(MAX_PATH, szDumpDir);
    wsprintf(szDumpFile, _T("%s\\%04d%02d%02d_%02d%02d%02d.dmp"), szDumpDir,
             stTime.wYear, stTime.wMonth, stTime.wDay,
             stTime.wHour, stTime.wMinute, stTime.wSecond);

    // 创建Dump文件;
    HANDLE hDumpFile = CreateFile(szDumpFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
    dumpInfo.ExceptionPointers = pException;
    dumpInfo.ThreadId = GetCurrentThreadId();
    dumpInfo.ClientPointers = TRUE;

    // 写入Dump文件内容
    MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hDumpFile, MiniDumpNormal, &dumpInfo, NULL, NULL);
    CloseHandle(hDumpFile);

    return EXCEPTION_EXECUTE_HANDLER;
}
#endif // _DEBUG
#endif // _WIN32

void signal_exit_handler()
{
    exit(0);
}

int main()
{
    //atexit(signal_exit_handler);

#ifdef _DEBUG
    SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)MinidumpCrashHandler);
#endif // _DEBUG

    gLog->init_log("./client_server.log", 1);

#ifdef _WIN32
    WSADATA wsaData;

    int wVersionRequested = MAKEWORD(2, 2);
    int iResult = WSAStartup(wVersionRequested, &wsaData);
    if (iResult != 0)
    {
        WSACleanup();
        wprintf(L"WSAStartup failed: %d\n", iResult);
        return -1;
    }
#endif

    std::string addr = "192.168.2.149:9099";

    evpp::EventLoop loop;
    evpp::TCPClient client(&loop, addr, "TCPPingPongClient");
    client.SetMessageCallback([&loop, &client](const evpp::TCPConnPtr & conn,
                              evpp::Buffer * msg)
    {
        LogDebug("Receive a message:{}", msg->ToString());
        //client.Disconnect();
    });

    //commlib::NetProxy* gNet = new commlib::NetProxy();
    client.SetConnectionCallback([/*gNet*/](const evpp::TCPConnPtr & conn)
    {
        //if (conn->IsConnected())
        //{
        //    LogDebug("Connected to:{}", conn->remote_addr());
        //    //conn->Send("hello");
        //    //conn->Send("hello world");

        //    string ss = "";
        //    for (auto i = 0; i < 75495; i++)
        //    {
        //        std::ostringstream  os;
        //        os << 1;
        //        ss += os.str();
        //    }
        //    LogDebug("sendlen:{}", ss.length());
        //    gNet->SendProto(conn, 1, const_cast<char*>(ss.c_str()), ss.length());
        //}
        //else
        //{
        //    conn->loop()->Stop();
        //}
    });
    client.Connect();
    loop.Run();

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

#ifdef _WIN32
    WSACleanup();
#endif //_WIN32

    return 0;
}