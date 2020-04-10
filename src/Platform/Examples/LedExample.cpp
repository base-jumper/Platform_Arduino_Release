#include "LedExample.h"

/* This example turns on a LED in response to a digital input changing state */

#include "../Shared/BaseJumper.h"


namespace BaseJumper
{
	static Led::Handle led(0); // construct object to control LED 0
	
	void update()
	{
		led.create(); // create the led
		led.set_state(Led::State_On); // turn LED on
	}
}
