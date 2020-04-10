#include "Client.h"

namespace BaseJumper
{
	Client::Client(ExceptionHandler handler_fptr_in)
		: handler_fptr(handler_fptr_in)
	{
	}
	
	void Client::init()
	{
	
	}
	
	void Client::deinit()
	{
	
	}
	
	void Client::send_command(Header header, const uint8_t* p_args, ARG_OUT uint8_t* p_result)
	{
	  // run the command
	  auto exception = send_command_impl(header, p_args, ARG_OUT p_result);
	  
	  // exception handling
	  if (!exception.is_none())
	  {
	    // Allow the application to handle the exception
	    Exception e(*this, header,exception);
		handler_fptr(e);
	  }
	}
	
	Client::Exception::Exception(Client& client_in, Header header_in, ExceptionData exception_data_in)
	  : client(client_in), header(header_in), exception_data(exception_data_in)
	{
	}
	
	void Client::invalidate_result(uint8_t* p_result, uint8_t result_len)
	{
		// Set response to an invalid value so application doesn't
		// treat it as a real value.
		for (size_t i = 0; i < result_len; i++)
			p_result[i] = 0xFF;
	}
}
