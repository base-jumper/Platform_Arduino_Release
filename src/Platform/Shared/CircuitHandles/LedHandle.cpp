#include "LedHandle.h"

namespace BaseJumper
{
	namespace Led
	{
		Handle::Handle(uint8_t board_id, Circuit::CircuitNum circuit_num, Client& client) 
			: CircuitHandle(board_id, Circuit::Type_Led, circuit_num, client)
		{
		}
	
		Handle::Handle(uint8_t board_id, Circuit::CircuitNum circuit_num)
		: CircuitHandle(board_id, Circuit::Type_Led, circuit_num)
		{
		}
	
		Handle::Handle(Circuit::CircuitNum circuit_num)
		: CircuitHandle(Circuit::Type_Led, circuit_num)
		{
		}
	
		void Handle::set_state(State state)
		{
			request_action1<State>(Instruction_SetState, set_state_info, state);
		}
	
		State Handle::get_state(void)
		{
			return request_func<State>(Instruction_GetState, get_state_info);
		}
	
		void Handle::set_blink_period(uint16_t period_ms)
		{
			request_action1<uint16_t>(Instruction_SetBlinkPeriod, set_blink_period_info, period_ms);
		}
	
		uint16_t Handle::get_blink_period(void)
		{
			return request_func<uint16_t>(Instruction_GetBlinkPeriod, get_blink_period_info);
		}
	}
}
