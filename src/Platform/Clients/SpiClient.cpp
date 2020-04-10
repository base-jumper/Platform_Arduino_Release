#include "SpiClient.h"
#include "stdio.h"

namespace BaseJumper
{
	SpiClient::SpiClient(ISpi& spi_in, IGpioPin& ss_in, IGpioPin& busy_in, ExceptionHandler handler_fptr_in)
	  : Client(handler_fptr_in), spi(spi_in), ss(ss_in), busy(busy_in)
	{
	}
	
	void SpiClient::init()
	{
	  busy.set_direction(IGpioPin::Direction_Input);
	  ss.set_level(true);
	  ss.set_direction(IGpioPin::Direction_Output);  
	}
	
	ExceptionData SpiClient::send_command_impl(const Header header, const uint8_t* p_args, ARG_OUT uint8_t* p_result)
	{
	  ExceptionData exception;
	
	  // transmit header
	  header.encode(tx_buffer);
	  wait_for_start(); // sync with server
	  spi.transfer(tx_buffer, rx_buffer, Header::encoded_len);
	  end();
	
	  // check header was received
	  if (!header_ack_received(rx_buffer))
	  {
	    invalidate_result(p_result, header.result_len);
	    return ExceptionData::protocol_error();
	  }
	
	  // args
	  if (header.arg_len > 0)
	  {
		  memcpy(tx_buffer, p_args, header.arg_len);
		  wait_for_start();
		  spi.transfer(tx_buffer, rx_buffer, header.arg_len);
		  end();
	
		  // check args were received
		  if (!arg_ack_received(rx_buffer, header.arg_len)) //TODO: change check so that it can be compiled out.
		  {
			invalidate_result(p_result, header.result_len);
			return ExceptionData::protocol_error();
		  }
	  }
	
	  // result
	  wait_for_start();
	  uint8_t rx = spi.transfer(poll_character);
	  if (rx == header_successful_character)
	  {
	    exception = ExceptionData::none();
	
		if (header.result_len > 0)
		{
			memset(tx_buffer, 0, header.result_len);
			spi.transfer(tx_buffer, rx_buffer, header.result_len);
			memcpy(p_result, rx_buffer, header.result_len);
		}
	  }
	  else // An exception occurred.
	  {
	    // The byte received was the first byte of the exception.
	    // Retrieve the remaining bytes.
	    rx_buffer[0] = rx;
	    spi.transfer(tx_buffer, &rx_buffer[1], ExceptionData::size - 1);
	    exception = ExceptionData::decode(rx_buffer);
	    invalidate_result(p_result, header.result_len);
	  }
	  end();
	  return exception;
	}
	
	bool SpiClient::header_ack_received(uint8_t* p_data)
	{
	  return memcmp(p_data, header_ack, sizeof(header_ack)) == 0;
	}
	
	bool SpiClient::arg_ack_received(uint8_t* p_data, uint8_t len)
	{
		for (int i = 0; i < len; i++)
		{
			if (p_data[i] != (Header::encoded_len + 1 + i))
				return false;
		}
		return true;
	}
	
	void SpiClient::wait_for_start()
	{ 
	  while (!busy.get_level()) ;
	  ss.set_level(false);
	  // Wait for server to acknowledge SS. otherwise there will be race-condition 
	  // between completion of SPI transfer and asserting the busy pin.
	  while (busy.get_level()) ;
	}
	
	void SpiClient::end()
	{
	  ss.set_level(true);
	}
}
