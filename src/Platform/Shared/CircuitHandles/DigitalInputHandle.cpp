#include "DigitalInputHandle.h"
#include "../../Shared/ValueTypes/CommonTypes.h"

namespace BaseJumper
{
	namespace DigitalInput
	{
		Handle::Handle(uint8_t board_id, Circuit::CircuitNum circuit_num, Client& client)
		: CircuitHandle(board_id, Circuit::Type_DigitalInput, circuit_num, client)
		{
		}
	
		Handle::Handle(uint8_t board_id, Circuit::CircuitNum circuit_num)
		: CircuitHandle(board_id, Circuit::Type_DigitalInput, circuit_num)
		{
		}
	
		Handle::Handle(Circuit::CircuitNum circuit_num)
		: CircuitHandle(Circuit::Type_DigitalInput, circuit_num)
		{
		}
	
		bool Handle::get_state()
		{
			return request_func<bool>(Instruction_GetState, get_state_info);
		}
	}
}
