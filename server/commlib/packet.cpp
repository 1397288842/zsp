#include "packet.h"
#include "evpp/slice.h"
namespace commlib
{
    int32_t Packet::ReadBuffer(evpp::Buffer* msg)
    {
        if (nullptr == msg)
        {
            LogError("evpp buffer is null");
            return -1;
        }

        int16_t head_len = PACKET_HEADER_SIZE;
        auto body_len = PeekMsgLen(msg->data(), msg->length());
        if (head_len + body_len > msg->length())
        {
            return 0;
        }

        head_buf_ = msg->NextString(head_len);
        head_data_ = (PkgHeader*)(head_buf_.c_str());
        body_buf_ = msg->NextString(head_data_->length);

        return (head_len + body_len);
    }

    int64_t Packet::GetCmd()
    {
        if (nullptr == head_data_)
        {
            return 0;
        }

        return head_data_->cmd;
    }

    int32_t Packet::PeekMsgLen(const char* data, int len)
    {
        assert(len >= PACKET_HEADER_SIZE);
        evpp::Slice result(data, PACKET_HEADER_SIZE);
        auto* info = (PkgHeader*)(result.data());

        return info->length;
    }

}