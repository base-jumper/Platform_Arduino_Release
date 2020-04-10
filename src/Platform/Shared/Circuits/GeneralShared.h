/* 
* GeneralShared.h
*
* Created: 4/03/2019 9:11:50 PM
* Author: nbute
*/

#ifndef __GENERALSHARED_H__
#define __GENERALSHARED_H__

#include "../../Shared/SharedCommon.h"
#include "../../Shared/ClientServer/CircuitDefinitions.h"
#include "../../Shared/ValueTypes/CommonTypes.h"
#include "../../Shared/ClientServer/InstructionInfo.h"

namespace BaseJumper
{
	namespace General
	{
		static constexpr uint8_t general_instruction_offset = 200;
		static constexpr uint8_t num_general_instructions = 5;
		static constexpr Circuit::InstructionNum first_general_instruction = general_instruction_offset;
		static constexpr Circuit::InstructionNum last_general_instruction = general_instruction_offset + num_general_instructions - 1; 
	
		/* Instruction Enum */
		enum {
			Instruction_GetApiVersion = general_instruction_offset,
			Instruction_Instructions,
			Instruction_Create,
			Instruction_Created,
			Instruction_Destroy
		} Instruction;
	
		/* Value Types */
		extern Uint16Type api_version_type;
	
		/* Instructions */
		extern FuncInfo<uint16_t> get_api_version_info;
		extern ActionInfo instructions_info;
		extern ActionInfo create_info;
		extern FuncInfo<bool> created_info;
		extern ActionInfo destroy_info;
		extern IInstructionInfo* general_instructions[num_general_instructions];
	
		/* Interface */
		class Interface {
			///virtual uint16_t get_api_version() = 0;
			//virtual void instructions();
			virtual void create() = 0;
			virtual bool created() = 0;
			virtual void destroy() = 0;
		};
	};
}

#endif //__GENERALSHARED_H__
