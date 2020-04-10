/*
 * LedShared.h
 *
 * Created: 4/01/2019 1:01:06 PM
 *  Author: nbute
 */ 


#ifndef LEDSHARED_H_
#define LEDSHARED_H_

#include "../../Shared/ClientServer/InstructionInfo.h"
#include "../../Shared/SharedCommon.h"
#include "../../Shared/ValueTypes/CommonTypes.h"

namespace BaseJumper
{
	namespace Led
	{
		/* Instruction Enum */
		typedef enum
		{
			Instruction_SetState,
			Instruction_GetState,
			Instruction_SetBlinkPeriod,
			Instruction_GetBlinkPeriod,
			Num_Instructions
		} Instruction;
	
		/* Types */
		typedef enum
		{
			State_Off,
			State_On,
			State_Blink
		} State;
	
		/* Value Types */
		extern EnumType<State> state_type;
		extern Uint16Type period_ms_type;
	
		/* Instructions */
		extern Action1Info<Led::State> set_state_info;
		extern FuncInfo<Led::State> get_state_info;
		extern Action1Info<uint16_t> set_blink_period_info;
		extern FuncInfo<uint16_t> get_blink_period_info;
	
		/* Interface */
		class Interface
		{
			public:
			virtual void set_state(Led::State state) = 0;
			virtual Led::State get_state() = 0;
			virtual void set_blink_period(uint16_t period_ms) = 0;
			virtual uint16_t get_blink_period() = 0;
		};
	};
}


#endif /* LEDSHARED_H_ */
