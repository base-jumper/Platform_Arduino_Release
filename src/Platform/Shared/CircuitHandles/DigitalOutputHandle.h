#ifndef DIGITALOUTPUTHANDLE_H_INCLUDED
#define DIGITALOUTPUTHANDLE_H_INCLUDED

#include "../../Shared/SharedCommon.h"
#include "../../Shared/CircuitHandles/CircuitHandle.h"
#include "../../Shared/Circuits/DigitalOutputShared.h"

namespace BaseJumper
{
	namespace DigitalOutput
	{
		class Handle : public DigitalOutput::Interface, public CircuitHandle
		{
		  public:
			Handle(uint8_t board_id, Circuit::CircuitNum circuit_num, Client& client);
			Handle(uint8_t board_id, Circuit::CircuitNum circuit_num);
			Handle(Circuit::CircuitNum circuit_num = 0);
			void set_state(Tristate state);
			Status get_status(void);
			void reset_status(void);
		};
	}
}
#endif //DIGITALOUTPUTHANDLE_H_INCLUDED
