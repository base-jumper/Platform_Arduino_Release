/*
 * CanClientServer.h
 *
 * Created: 16/05/2019 10:05:10 PM
 *  Author: nbute
 */ 


#ifndef CANCLIENTSERVER_H_
#define CANCLIENTSERVER_H_

namespace BaseJumper
{
	class CanClientServer
	{
	protected:
		enum MsgType
		{
			MsgType_Header,
			MsgType_Args,
			MsgType_Result,
			MsgType_Exception
		};
	
		struct MsgId
		{
			static constexpr uint8_t sandwich_protocol = 0x0F;
			static constexpr uint8_t protocol_position = 24;
			static constexpr uint32_t protocol_mask = 0x1F << protocol_position;
			static constexpr uint8_t msg_type_position = 16;
			static constexpr uint32_t msg_type_mask = 0xFF << msg_type_position;
			static constexpr uint8_t src_board_position = 8;
			static constexpr uint32_t src_board_mask = 0xFF << src_board_position;
			static constexpr uint8_t dst_board_position = 0;
			static constexpr uint32_t dst_board_mask = 0xFF << dst_board_position;
	
			MsgType msg_type;
			uint8_t src_board;
			uint8_t dst_board;
	
			static Can::IdMask get_default_filter(uint8_t board_id)
			{
				MsgId swid;
				swid.msg_type = MsgType_Header;
				swid.src_board = 0;
				swid.dst_board = board_id;
				auto msg_id = swid.encode();
				return Can::IdMask(msg_id, protocol_mask | dst_board_mask);
			}
	
			Can::Id encode()
			{
				uint32_t val =
				((sandwich_protocol << protocol_position) & protocol_mask) |
				((msg_type << msg_type_position) & msg_type_mask) |
				((src_board << src_board_position) & src_board_mask) |
				((dst_board << dst_board_position) & dst_board_mask);
				return Can::Id::ext(val);
			}
		
			static bool try_decode(Can::Id msg_id, ARG_OUT MsgId& result)
			{
				if (msg_id.is_std())
					return false;
				uint8_t protocol = (msg_id.value & protocol_mask) >> protocol_position;
				if (protocol != sandwich_protocol)
					return false;
				result.msg_type = static_cast<MsgType>((msg_id.value & msg_type_mask) >> msg_type_position);
				result.src_board = (msg_id.value & src_board_mask) >> src_board_position;
				result.dst_board = (msg_id.value & dst_board_mask) >> dst_board_position;
				return true;
			}
	
			MsgId()
			{
	
			}
	
			MsgId(MsgType msg_type_in, uint8_t src_board_in, uint8_t dst_board_in)
			: msg_type(msg_type_in), src_board(src_board_in), dst_board(dst_board_in)
			{
				
			}
		};
	
		static constexpr uint8_t max_message_len = 16;
	};
}

#endif /* CANCLIENTSERVER_H_ */
