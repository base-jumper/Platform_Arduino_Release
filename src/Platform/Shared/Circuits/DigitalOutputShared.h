#ifndef DIGITALOUTPUT_SHARED_H_INCLUDED
#define DIGITALOUTPUT_SHARED_H_INCLUDED

#include "../../Shared/ClientServer/Header.h"
#include "../../Shared/ValueTypes/CommonTypes.h"
#include "../../Shared/ClientServer/InstructionInfo.h"

namespace BaseJumper
{
	namespace DigitalOutput
	{
		/* Instruction Enum */
		typedef enum
		{
			Instruction_SetState,
			Instruction_GetStatus,
			Instruction_ResetStatus,
			Num_Instructions
		} Instruction;
	
		/* Types */
		typedef enum
		{
			Status_Ok,
			Status_OverloadShutdown
		} Status;
		
		/* Value Types */
		extern EnumType<Status> status_type;
		extern TristateEnum state_type;
	
		/* Instructions */
		extern Action1Info<Tristate> set_state_info;
		extern FuncInfo<Status> get_status_info;
		extern ActionInfo reset_status_info;
	
	    /* Interface */
		class Interface
		{
		public:
			virtual void set_state(Tristate state) = 0;
			virtual Status get_status(void) = 0;
			virtual void reset_status(void) = 0;
		};
	};
}

#endif //DIGITALOUTPUT_SHARED_H_INCLUDED
