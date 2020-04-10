#ifndef PLATFORM_H_
#define PLATFORM_H_

#include "Resources/ISpi.h"
#include "Resources/IGpioPin.h"
#include "Clients/SpiClient.h"

/* Variable & functions to be implemented in platform-specific file */
namespace BaseJumper
{
	extern ISpi& ctl_client_spi;		// spi used for circuit client
	extern IGpioPin& ctl_client_busy_pin;	// busy pin used by circuit client
	extern IGpioPin& ctl_client_ss_pin;    // slave select pin used by circuit client
	
	extern void platform_init(); // executes platform-specific initialisations
}

#endif /* PLATFORM_H_ */
