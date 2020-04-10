#include "GpioAdaptor.h"
#include <Arduino.h>

namespace BaseJumper
{

	GpioAdaptor::GpioAdaptor(const uint8_t pin_num_in)
	: pin_num(pin_num_in)
	{
	}

	void GpioAdaptor::set_direction(IGpioPin::Direction dir)
	{
		pinMode(pin_num, dir == IGpioPin::Direction_Output ? OUTPUT : INPUT);
	}

	void GpioAdaptor::set_level(bool level)
	{
		digitalWrite(pin_num, level ? HIGH : LOW);
	}

	bool GpioAdaptor::get_level()
	{
		return digitalRead(pin_num);
	}

}