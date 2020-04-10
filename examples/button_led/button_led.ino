#include <BaseJumper.h>

using namespace BaseJumper;

// create circut handles
static DigitalInput::Handle button(0);
static Led::Handle led(0);

void setup() 
{  
  basejumper_init();

  led.create();
  button.create();
}

void loop() 
{
    /* Turn led on when button is pressed and off when button is released */
    if (button.get_state())
    {
      led.set_state(Led::State_On);
    }
    else
    {
      led.set_state(Led::State_Off);
    }
    delay(50);
}