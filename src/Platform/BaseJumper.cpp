#include "Shared/BaseJumper.h"
#include "Platform.h"

namespace BaseJumper
{
	void exception_handler(Client::Exception e) __attribute__((weak));
	
	static Client::ExceptionHandler exception_handler_fptr;
	SpiClient spi_client(ctl_client_spi, ctl_client_ss_pin, ctl_client_busy_pin, exception_handler);
	Client& default_client = spi_client;
	
	void basejumper_init()
	{
		platform_init();
		ctl_client_spi.init();
		spi_client.init();
	}
	
	void basejumper_register_exception_handler(Client::ExceptionHandler exception_handler_fptr_in)
	{
		exception_handler_fptr = exception_handler_fptr_in;
	}
	
	void exception_handler(Client::Exception e)
	{
		if (exception_handler_fptr != NULL)
			(*exception_handler_fptr)(e);
	}
}
