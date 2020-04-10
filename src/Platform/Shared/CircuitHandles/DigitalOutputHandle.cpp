#include "DigitalOutputHandle.h"
#include "../../Shared/ValueTypes/TristateEnum.h"

namespace BaseJumper
{
	namespace DigitalOutput
	{
		Handle::Handle(uint8_t board_id, Circuit::CircuitNum circuit_num, Client& client) 
		  : CircuitHandle(board_id, Circuit::Type_DigitalOutput, circuit_num, client)
		{
		}
	
		Handle::Handle(uint8_t board_id, Circuit::CircuitNum circuit_num)
		: CircuitHandle(board_id, Circuit::Type_DigitalOutput, circuit_num)
		{
		}
		
		Handle::Handle(Circuit::CircuitNum circuit_num)
		: CircuitHandle(Circuit::Type_DigitalOutput, circuit_num)
		{
		}

		void Handle::set_state(Tristate state)
		{
			request_action1<Tristate>(Instruction_SetState, set_state_info, state);
		}
	
		Status Handle::get_status(void)
		{
			return request_func<Status>(Instruction_GetStatus, get_status_info);
		}
	
		void Handle::reset_status(void)
		{
			request_action(Instruction_ResetStatus, reset_status_info);
		}
	}
}
