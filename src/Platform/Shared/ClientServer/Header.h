#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include "../../Shared/SharedCommon.h"
#include "../../Shared/ClientServer/BoardDefinitions.h"
#include "../../Shared/ClientServer/CircuitDefinitions.h"
#include "../../Shared/ClientServer/Exception.h"
#include "../../Shared/ClientServer/InstructionInfo.h"


namespace BaseJumper
{
	struct Header
	{
	  public:
	    static constexpr uint8_t encoded_len = 6;
	    static Header invalid;
	
	    uint8_t board_id;
	    Circuit::Type circuit_type;
	    Circuit::CircuitNum circuit_num;
	    uint8_t instruction;
		uint8_t arg_len;
		uint8_t result_len;
	
		Header();
	
	    Header(
	      uint8_t board_id_in, 
	      Circuit::Type circuit_type_in,
	      Circuit::CircuitNum circuit_num_in,
	      uint8_t instruction_in,
		  uint8_t arg_len_in,
		  uint8_t result_len_in);
	    void encode(uint8_t* p_dest) const;
	    static Header decode(const uint8_t* p_encoded_header);
	};
}

#endif //HEADER_H_INCLUDED
