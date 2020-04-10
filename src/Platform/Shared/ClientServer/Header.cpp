#include "../../Shared/ClientServer/Header.h"
#include <string.h>

namespace BaseJumper
{
	Header Header::invalid = Header(Board_Invalid, Circuit::Type_Invalid, Circuit::circuit_num_invalid, Circuit::instruction_invalid, 0, 0);
	
	Header::Header()
	{
	}
	
	Header::Header(
	  uint8_t board_id_in, 
	  Circuit::Type circuit_type_in,
	  Circuit::CircuitNum circuit_num_in,
	  uint8_t instruction_in,
	  uint8_t arg_len_in,
	  uint8_t result_len_in)
	  :   board_id(board_id_in), 
	      circuit_type(circuit_type_in), 
	      circuit_num(circuit_num_in),
	      instruction(instruction_in),
		  arg_len(arg_len_in),
		  result_len(result_len_in)
	{
	}
	
	void Header::encode(uint8_t* p_dest) const
	{
	  p_dest[0] = board_id;
	  p_dest[1] = circuit_type;
	  p_dest[2] = circuit_num;
	  p_dest[3] = instruction;
	  p_dest[4] = arg_len;
	  p_dest[5] = result_len;
	}
	
	Header Header::decode(const uint8_t* p_encoded_header)
	{
	  auto board_id = p_encoded_header[0];
	  auto circuit_type = static_cast<Circuit::Type>(p_encoded_header[1]);
	  auto circuit_num = static_cast<Circuit::CircuitNum>(p_encoded_header[2]);
	  auto instruction = static_cast<uint8_t>(p_encoded_header[3]);
	  auto arg_len = static_cast<uint8_t>(p_encoded_header[4] & 0x3F);
	  auto result_len = static_cast<uint8_t>(p_encoded_header[5]);
	  return Header(
		board_id, 
		circuit_type, 
		circuit_num, 
		instruction, 
		arg_len,
		result_len
		);
	}
}
