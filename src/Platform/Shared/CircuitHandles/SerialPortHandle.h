#ifndef SERIALHANDLE_H_
#define SERIALHANDLE_H_

#include "../../Shared/SharedCommon.h"
#include "../../Shared/CircuitHandles/CircuitHandle.h"
#include "../../Shared/Circuits/SerialPortShared.h"

namespace BaseJumper
{
	namespace SerialPort
	{
		class Handle : public Interface, public CircuitHandle
		{
			public:
			Handle(uint8_t board_id, Circuit::CircuitNum circuit_num, Client& client);
			Handle(uint8_t board_id, Circuit::CircuitNum circuit_num);
			Handle(Circuit::CircuitNum circuit_num = 0);
			void start(uint32_t baud, Config config) override final;
			uint16_t available() override final;
			uint8_t read() override final;
			Array<uint8_t,8> read8() override final;
			void write(uint8_t) override final;
			void write8(Array<uint8_t,8>) override final;
			void clear() override final;
			void read(ARG_OUT uint8_t* p_dest, size_t len) override final;
			void write(uint8_t* p_src, size_t len) override final;
		};
	}
}

#endif /* SERIALHANDLE_H_ */
