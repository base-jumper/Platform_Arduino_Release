/* 
* GeneralShared.cpp
*
* Created: 4/03/2019 9:11:50 PM
* Author: nbute
*/


#include "GeneralShared.h"
#include <limits.h>

namespace BaseJumper
{
	namespace General
	{
		/* Value Types */
		Uint16Type api_version_type("",0,UINT16_MAX);
		BoolType bt;
	
		/* Instructions */
		FuncInfo<uint16_t> get_api_version_info("get_api_version",api_version_type);
		ActionInfo instructions_info("instructions");
		ActionInfo create_info("create");
		FuncInfo<bool> created_info("created", bt);
		ActionInfo destroy_info("destroy");
		IInstructionInfo* general_instructions[num_general_instructions] = {
			&get_api_version_info,	// Instruction_ApiVersionGet
			&instructions_info,				// Instruction_Info
			&create_info,			// Instruction_Create
			&created_info,			// Instruction_Created
			&destroy_info			// Instruction_Destroy
			}; 
	}
}
