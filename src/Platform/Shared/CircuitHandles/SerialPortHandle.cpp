#include "SerialPortHandle.h"

namespace BaseJumper
{
	namespace SerialPort
	{
		Handle::Handle(
			uint8_t board_id, 
			Circuit::CircuitNum circuit_num, 
			Client& client)
			: CircuitHandle(board_id, Circuit::Type_Serial, circuit_num, client)
		{
		}
	
		Handle::Handle(uint8_t board_id, Circuit::CircuitNum circuit_num)
		: CircuitHandle(board_id, Circuit::Type_Serial, circuit_num)
		{
		}
		
		Handle::Handle(Circuit::CircuitNum circuit_num)
		: CircuitHandle(Circuit::Type_Serial, circuit_num)
		{
		}

		void Handle::start(uint32_t baud, Config config)
		{
			request_action2<uint32_t,Config>(Instruction_Start, start_info, baud, config);
		}

		uint16_t Handle::available()
		{
			return request_func<uint16_t>(Instruction_Available, available_info);
		}
	
		uint8_t Handle::read()
		{
			return request_func<uint8_t>(Instruction_Read, read_info);
		}
	
		Array<uint8_t,8> Handle::read8()
		{
			return request_func<Array<uint8_t,8>>(Instruction_Read8, read8_info);
		}
	
		void Handle::write(uint8_t data)
		{
			request_action1<uint8_t>(Instruction_Write, write_info, data);
		}
	
		void Handle::write8(Array<uint8_t,8> data)
		{
			request_action1<Array<uint8_t,8>>(Instruction_Write8, write8_info, data);
		}
	
		void Handle::clear()
		{
			request_action(Instruction_Clear, clear_info);
		}
	
		void Handle::read(ARG_OUT uint8_t* p_dest, size_t len)
		{
			size_t i = 0;
			auto remaining = len;
			while (remaining >= 8)
			{
				auto data = read8();
				memcpy(&p_dest[i],data.items,8);
				remaining -= 8;
				i += 8;
			}
			while (remaining >= 1)
			{
				auto data = read();
				p_dest[i] = data;
				remaining--;
				i++;
			}
		}
	
		void Handle::write(uint8_t* p_src, size_t len)
		{
			size_t i = 0;
			auto remaining = len;
			while (remaining >= 8)
			{
				Array<uint8_t,8> arr(&p_src[i]);
				write8(arr);
				remaining -= 8;
				i += 8;
			}
			while (remaining >= 1)
			{
				write(p_src[i]);
				remaining--;
				i++;
			}
		}
	}
}
