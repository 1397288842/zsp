#pragma once
#include "common.h"

#include "evpp/buffer.h"

namespace commlib
{
#pragma pack(1)
    typedef struct _PkgHeader
    {
        int32_t  length{ 0 }; //包体长度
        int64_t  cmd{ 0 };
        int32_t  rand_code{ 0 };
        int8_t   version{ 0 };
        int8_t   rand1{ 0 };
        int8_t   rand2{ 0 };
    } PkgHeader;
#pragma pack()
    enum
    {
        PACKET_HEADER_SIZE = sizeof(PkgHeader),
    };

    class Packet
    {
    public:
        Packet() = default;
        ~Packet() = default;

    public:
        int32_t ReadBuffer(evpp::Buffer* msg);
        int64_t GetCmd();
        int32_t PeekMsgLen(const char* data, int len);

    private:
        PkgHeader* head_data_;
        string head_buf_;
        string body_buf_;
        bool read_all_; //是否读完整包
    };
}