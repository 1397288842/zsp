#ifndef __PACKET_H__
#define __PACKET_H__

#include "common.h"

#include "evpp/buffer.h"

// 1字节 客户端包序号
constexpr int CLIENT_SEQ_LEN = 1;

// 2字节 客户端包头
constexpr int CLIENT_HEADER_LENGTH = 2;

// 4字节 服务器包头
constexpr int SERVER_HEADER_LENTH = 4;

// 2字节 协议号
constexpr int CMD_ID_LENGTH = 2;

// 客户端包组成
constexpr int CLIENT_PACKET_HEADER_LENGTH = CLIENT_HEADER_LENGTH + CLIENT_SEQ_LEN + CMD_ID_LENGTH;

// 服务器包组成
constexpr int SERVER_PACKET_HEADER_LENGTH = SERVER_HEADER_LENTH + CMD_ID_LENGTH;

namespace commlib
{
	enum class PackType {
		PT_SERVER = 0, // 服务器类型
		PT_CLIENT = 1, // 客户端类型
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
		bool read_all_; //是否读完整包
	};
}

#endif // __PACKET_H__

