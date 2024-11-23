// gateway_server.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "global.h"
#include "log.hpp"
#include <iostream>
#include "gateway_server.h"
#include "common.h"

#ifdef _WIN32
#include <Windows.h>
#ifdef _DEBUG
#include <tchar.h>
#include <DbgHelp.h>
#pragma comment(lib, "dbghelp.lib")
#endif // _DEBUG
#endif // _WIN32

#include <evpp/tcp_server.h>
#include <evpp/buffer.h>
#include <evpp/tcp_conn.h>

#include "net_proxy.h"

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

auto gLog = std::make_shared<commlib::GlobalLog>();

int main()
{
#ifdef _DEBUG
    SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)MinidumpCrashHandler);
#endif // _DEBUG

    gLog->init_log("./testt.log", 1);

    WSADATA wsaData;

    int wVersionRequested = MAKEWORD(2, 2);
    int iResult = WSAStartup(wVersionRequested, &wsaData);
    if (iResult != 0)
    {
        WSACleanup();
        wprintf(L"WSAStartup failed: %d\n", iResult);
        return -1;
    }
    std::string addr = "0.0.0.0:9099";
    int thread_num = 4;
    evpp::EventLoop loop;
    evpp::TCPServer server(&loop, addr, "TCPEchoServer", thread_num);
    commlib::NetProxy* gNet = new commlib::NetProxy();
    server.SetMessageCallback([gNet](const evpp::TCPConnPtr & conn,
                                     evpp::Buffer * msg)
    {
        LogDebug("Receive a message len:{}", msg->length());

        if (gNet->packet_.ReadBuffer(msg))
        {
            conn->Send("shoudao");
        }
    });
    server.SetConnectionCallback([](const evpp::TCPConnPtr & conn)
    {
        if (conn->IsConnected())
        {
            LogInfo( "A new connection from:{} ", conn->remote_addr());
        }
        else
        {
            LogInfo("Lost the connection from:{}  ", conn->remote_addr());
        }
    });
    server.Init();
    server.Start();
    loop.Run();

#ifdef _WIN32
    WSACleanup();
#endif //_WIN32

    return 0;
}
