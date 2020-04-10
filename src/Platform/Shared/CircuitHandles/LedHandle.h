#ifndef LEDHANDLE_H_INCLUDED
#define LEDHANDLE_H_INCLUDED

#include "../../Shared/SharedCommon.h"
#include "../../Shared/CircuitHandles/CircuitHandle.h"
#include "../../Shared/Circuits/LedShared.h"

namespace BaseJumper
{
	namespace Led
	{
		class Handle : public Interface, public CircuitHandle
		{
		  public:
			Handle(uint8_t board_id, Circuit::CircuitNum circuit_num, Client& client);
			Handle(uint8_t board_id, Circuit::CircuitNum circuit_num);
			Handle(Circuit::CircuitNum circuit_num = 0);
			void set_state(State state) override final;
			State get_state(void) override final;
			void set_blink_period(uint16_t) override final;
			uint16_t get_blink_period(void) override final;
		};
	}
}
#endif //LEDHANDLE_H_INCLUDED
