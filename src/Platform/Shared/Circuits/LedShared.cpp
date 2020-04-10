/*
 * LedShared.cpp
 *
 * Created: 4/01/2019 1:00:50 PM
 *  Author: nbute
 */ 

#include "LedShared.h"
#include "../../Shared/ValueTypes/CommonTypes.h"

namespace BaseJumper
{
	namespace Led
	{
		/* Value Types */
		const char* state_names[] = { "off", "on", "blink" };
		EnumType<State> state_type(state_names, 3);
		Uint16Type blink_period_type("ms",100,2000);
	 
		/* Instructions */
		Action1Info<State> set_state_info("set_state", state_type);
		FuncInfo<State> get_state_info("get_state", state_type);
		Uint16Type period_ms_type("ms",100,2000);
		Action1Info<uint16_t> set_blink_period_info("set_blink_period", period_ms_type);
		FuncInfo<uint16_t> get_blink_period_info("get_blink_period", period_ms_type);
	
	}
}
