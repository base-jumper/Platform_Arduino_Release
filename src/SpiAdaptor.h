/* 
* SpiAdaptor.h
*
* Pins must be configured externally (MISO, MOSI, SCLK).
* Transfer function is blocking.
* Bit rate is fixed at 1MHz.
* Chip select not controlled by peripheral. Control externally as a port pin instead.
* CPOL/CPHA settings fixed (clock low when idle, capture data on the second clock edge)
*/


#ifndef __SPIADAPTOR_H__
#define __SPIADAPTOR_H__

#include "Platform/PlatformCommon.h"
#include "Platform/Resources/IGpioPin.h"
#include "Platform/Resources/ISpi.h"

namespace BaseJumper
{
    class SpiAdaptor : public ISpi
    {
    private:

    public:
        SpiAdaptor();

        void init() override final;
        
        void deinit() override final;
        
        void transfer(uint8_t* tx_data, ARG_OUT uint8_t* rx_data, uint8_t data_len) override final;
    };
}

#endif //__SPIADAPTOR_H__
