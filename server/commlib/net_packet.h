#ifndef __PACKET_H__
#define __PACKET_H__

#include "common.h"

#include "evpp/buffer.h"

// 1�ֽ� �ͻ��˰����
constexpr int CLIENT_SEQ_LEN = 1;

// 2�ֽ� �ͻ��˰�ͷ
constexpr int CLIENT_HEADER_LENGTH = 2;

// 4�ֽ� ��������ͷ
constexpr int SERVER_HEADER_LENTH = 4;

// 2�ֽ� Э���
constexpr int CMD_ID_LENGTH = 2;

// �ͻ��˰����
constexpr int CLIENT_PACKET_HEADER_LENGTH = CLIENT_HEADER_LENGTH + CLIENT_SEQ_LEN + CMD_ID_LENGTH;

// �����������
constexpr int SERVER_PACKET_HEADER_LENGTH = SERVER_HEADER_LENTH + CMD_ID_LENGTH;

namespace commlib
{
	enum class PackType {
		PT_SERVER = 0, // ����������
		PT_CLIENT = 1, // �ͻ�������
	};

	class NetPacket
	{
	public:
		NetPacket() = default;
		~NetPacket() = default;

	public:
		int32_t ReadBuffer(evpp::Buffer* msg);
		const uint32_t& Cmd();
		void SetType(PackType type);
		const evpp::Slice& GetMsg();

		void WrapMsg(uint32_t cmd, const evpp::Slice& msg);
	private:
		void ReadServer(evpp::Buffer* msg);
		void ReadClient(evpp::Buffer* msg);

	private:
		uint32_t len_;
		uint32_t cmd_;
		PackType type_;
		evpp::Slice msg_;
		bool read_all_; //�Ƿ��������
	};
}

#endif // __PACKET_H__

