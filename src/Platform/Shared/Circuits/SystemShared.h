/* 
* SystemShared.h
*
* Created: 29/06/2019 8:06:13 PM
* Author: nbute
*/


#ifndef __SYSTEMSHARED_H__
#define __SYSTEMSHARED_H__

#include "../../Shared/ClientServer/InstructionInfo.h"
#include "../../Shared/SharedCommon.h"
#include "../../Shared/ValueTypes/CommonTypes.h"

namespace BaseJumper
{
	namespace System
	{
		/* Instruction Enum */
		enum Instruction
		{
			Instruction_Faults,
			Instruction_ClearFaults,
			Instruction_SetDummyFault,
			Instruction_ResetDummyFault,
			Instruction_Circuits,
			Instruction_SetBoardId,
			Instruction_GetBoardId,
			Num_Instructions
		};
		
		/* Instructions */
		extern ActionInfo faults_info;
		extern ActionInfo clear_faults_info;
		extern ActionInfo set_dummy_fault_info;
		extern ActionInfo reset_dummy_fault_info;
		extern ActionInfo circuits_info;
		extern FuncInfo<uint8_t> get_board_id_info;
		extern Action1Info<uint8_t> set_board_id_info;
	
		/* Interface */
		class Interface
		{
			public:
			//virtual void set_address() = 0;
			//virtual void print_address() = 0;
			virtual void faults() = 0;
			virtual void clear_faults() = 0;
			
			// used for testing faults. Sets the state of dummy_fault.
			virtual void set_dummy_fault() = 0;
			virtual void reset_dummy_fault() = 0;
			
			virtual uint8_t get_board_id() = 0;
			virtual void set_board_id(uint8_t id) = 0;

			virtual void circuits() = 0;
		};
	}
}

#endif //__SYSTEMSHARED_H__
