#ifndef SPICLIENT_H_INCLUDED
#define SPICLIENT_H_INCLUDED

#include "../PlatformCommon.h"
#include "../Shared/ClientServer/SpiClientServer.h"
#include "../Shared/ClientServer/Header.h"
#include "../Resources/ISpi.h"
#include "../Resources/IGpioPin.h"
#include "../Shared/Clients/Client.h"

namespace BaseJumper
{
	class SpiClient : public Client, public SpiClientServer
	{
	  private:
	    ISpi& spi;
	    IGpioPin& ss; 
	    IGpioPin& busy;
	    uint8_t tx_buffer[max_message_len];
	    uint8_t rx_buffer[max_message_len];
		
	    bool header_ack_received(uint8_t* p_data);
		bool arg_ack_received(uint8_t* p_data, uint8_t len);
	    void wait_for_start();
	    void end();
	
	  public:
	    SpiClient(ISpi& spi, IGpioPin& ss, IGpioPin& busy, ExceptionHandler handler_fptr_in);
	    void init() override final;
	    ExceptionData send_command_impl(const Header header, const uint8_t* p_args, ARG_OUT uint8_t* p_result) override final;
	};
}

#endif //SPICLIENT_H_INCLUDED
