#include "../../Shared/ClientServer/Exception.h"
#include "../../Shared/Circuits/DigitalInputShared.h"
#include "../../Shared/Circuits/DigitalOutputShared.h"
#include <string.h>

namespace BaseJumper
{
	OStream& ExceptionData::print(OStream& os) const
	{
		switch (code)
		{
			case Code_None:
				return os << "Success.";
			case Code_ResourceConflict:
				//TODO: print details of circuit that is using resource!
				return os << "Required resource is already used by another circuit.";
			case Code_CircuitNotCreated:
				return os << "Circuit has not been created.";
			case Code_InstructionInvalid:
				return  os << "Invalid instruction.";
			case Code_CircuitNumberInvalid:
				return os << "Invalid circuit number. There are " << args[0] << " instances of this circuit available.";
			case Code_ArgumentsLengthInvalid:
				return os << "Supplied arguments were not of the expected length.";
			case Code_BoardInvalid:
				return os << "Invalid board.";
			case Code_CircuitTypeInvalid:
				return os << "Circuit type invalid";
			case Code_ProtocolError:
				return os << "Protocol error";
			case Code_Unresolvable:
				return os << "Unresolvable.";
			default:
				return os;
		}
	}
	
	void ExceptionData::encode(uint8_t* p_dest)
	{
	  p_dest[0] = code;
	  p_dest[1] = args[0];
	  p_dest[2] = args[1];
	  p_dest[3] = args[2];
	}
	
	ExceptionData ExceptionData::highest_priority(ExceptionData e1, ExceptionData e2)
	{
	  return e1.code >= e2.code ? e1 : e2;
	}
	
	bool ExceptionData::is_high_priority()
	{
	  return code >= high_priority_threshold;
	}
}
