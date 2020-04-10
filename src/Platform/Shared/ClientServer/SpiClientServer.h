#ifndef SPICLIENTSERVER_H_INCLUDED
#define SPICLIENTSERVER_H_INCLUDED

#include "../../Shared/SharedCommon.h"
#include "../../Shared/ClientServer/BoardDefinitions.h"
#include "../../Shared/ClientServer/CircuitDefinitions.h"
#include "../../Shared/ClientServer/Header.h"

namespace BaseJumper
{
	class SpiClientServer
	{
	  protected: 
	    static uint8_t header_ack[Header::encoded_len];
	    static constexpr uint8_t poll_character = 0xFF;
	    static constexpr uint8_t header_successful_character = 0x00;
	    static constexpr uint8_t max_message_len = 16;
	};
}

#endif //SPICLIENTSERVER_H_INCLUDED
