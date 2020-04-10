#ifndef CIRCUIT_DEFINITIONS_H_INCLUDED
#define CIRCUIT_DEFINITIONS_H_INCLUDED

#include "../../Shared/SharedCommon.h"

namespace BaseJumper
{
	namespace Circuit
	{
		/* Types */
		typedef uint8_t CircuitNum;
		typedef uint8_t InstructionNum;
		constexpr uint8_t circuit_num_invalid = 0xFF;
		constexpr uint8_t instruction_invalid = 0xFF;
	
		/* Task: add circuit */
		/* Add new entry to the Circuit::Type enum, above the "Num_Types" entry.           */
		/* Follow the established naming convention. Entries should begin with "Type_".    */
		typedef enum {
			Type_System,
			Type_Led,
			Type_DigitalOutput,
			Type_DigitalInput,
			Type_Serial,
			// add new circuit here
			Num_Types,
			Type_Invalid = 0xFF,
		} Type;
	}
}


#endif //CIRCUIT_DEFINITIONS_H_INCLUDED
