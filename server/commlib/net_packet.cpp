#include "net_packet.h"
#include "evpp/slice.h"
namespace commlib
{
	int32_t NetPacket::ReadBuffer(evpp::Buffer* msg)
    {
        if (nullptr == msg)
        {
            LogError("evpp buffer is null");
            return -1;
        }

        if (type_ == PackType::PT_CLIENT)
        {
            ReadClient(msg);
        }
        else if (type_ == PackType::PT_SERVER)
        {
            ReadServer(msg);
        }
        else
        {
            LogError("type is error");
            return -1;
        }

        return 0;
    }

    const uint32_t& NetPacket::Cmd()
    {
        return cmd_;
    }


	void NetPacket::SetType(PackType type)
	{
        type_ = type;
	}


	const evpp::Slice& NetPacket::GetMsg()
	{
        return msg_;
	}

	void NetPacket::ReadServer(evpp::Buffer* msg)
	{
        // 4�ֽڳ���
		len_ = msg->ReadInt32();
        assert(len_ > SERVER_HEADER_LENTH);

		// 2�ֽ�Э���
		cmd_ = msg->ReadInt16();

		// ����
		msg_ = msg->Next(len_ - SERVER_HEADER_LENTH);
	}


	void NetPacket::ReadClient(evpp::Buffer* msg)
	{
        // 2�ֽڳ���
        len_ = msg->ReadInt16();
        assert(len_ > CLIENT_PACKET_HEADER_LENGTH);

        // 1�ֽ����к�
        msg->ReadInt8();

        // 2�ֽ�Э���
        cmd_ = msg->ReadInt16();

        // ����
        msg_ = msg->Next(len_ - CLIENT_PACKET_HEADER_LENGTH);
	}

}