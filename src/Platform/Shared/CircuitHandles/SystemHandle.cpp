#include "../../Shared/CircuitHandles/SystemHandle.h"

namespace BaseJumper
{
	namespace System
	{
		Handle::Handle(uint8_t board_id, Client& client)
		: CircuitHandle(board_id, Circuit::Type_System, 0, client)
		{
	
		}
	
		Handle::Handle(uint8_t board_id)
		: CircuitHandle(board_id, Circuit::Type_System, 0)
		{
			
		}

		void Handle::faults()
		{
			request_action(Instruction_Faults, faults_info);
		}
	
		void Handle::clear_faults()
		{
			request_action(Instruction_ClearFaults, clear_faults_info);
		}
	
		void Handle::set_dummy_fault()
		{
			request_action(Instruction_SetDummyFault, set_dummy_fault_info);
		}

		void Handle::reset_dummy_fault()
		{
			request_action(Instruction_ResetDummyFault, reset_dummy_fault_info);
		}
	
		void Handle::circuits()
		{
			request_action(Instruction_Circuits, circuits_info);
		}

		uint8_t Handle::get_board_id()
		{
			return request_func<uint8_t>(Instruction_GetBoardId, get_board_id_info);
		}

		void Handle::set_board_id(uint8_t id)
		{
			request_action1(Instruction_SetBoardId, set_board_id_info, id);
		}
	}
}
