#ifndef DIGITALINPUTHANDLE_H_INCLUDED
#define DIGITALINPUTHANDLE_H_INCLUDED

#include "../../Shared/SharedCommon.h"
#include "../../Shared/CircuitHandles/CircuitHandle.h"
#include "../../Shared/Circuits/DigitalInputShared.h"

namespace BaseJumper
{
	namespace DigitalInput
	{
		class Handle : public CircuitHandle, public DigitalInput::Interface
		{
		  public:
			Handle(uint8_t board_id, Circuit::CircuitNum circuit_num, Client& client);
			Handle(uint8_t board_id, Circuit::CircuitNum circuit_num);
			Handle(Circuit::CircuitNum circuit_num);
			bool get_state() override final;
		};
	}
}

#endif //DIGITALINPUTHANDLE_H_INCLUDED
