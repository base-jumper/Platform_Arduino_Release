#ifndef DIGITALINPUT_SHARED_H_INCLUDED
#define DIGITALINPUT_SHARED_H_INCLUDED

#include "../../Shared/ClientServer/InstructionInfo.h"
#include "../../Shared/ValueTypes/CommonTypes.h"

namespace BaseJumper
{
	namespace DigitalInput
	{
		/* Instruction Enum */
	    typedef enum
	    {
	      Instruction_GetState,
	      Num_Instructions
	    } Instruction;
	
		/* Value Types */
		extern BoolType state_type;
	
		/* Instructions */
		extern FuncInfo<bool> get_state_info;
		
		/* Interface */
		class Interface
		{
		  public:
			  virtual bool get_state() = 0;
		};
	};
}

#endif //DIGITALINPUT_SHARED_H_INCLUDED
