#include "SpiAdaptor.h"
#include <SPI.h>

namespace BaseJumper
{
	SpiAdaptor::SpiAdaptor()
	{
	}

	void SpiAdaptor::init()
	{
		SPI.begin();
		/* 
		beginTransaction is called once in init instead of for each call to transfer. The reason for this is that
		beginTransaction() can cause some unexpected transitions on the SCLK line. We don't want this to happen
		when the CS line is asserted. This behaviour was observed on a MKR WiFi.
		*/
		SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE1));
	}
		
	void SpiAdaptor::deinit()
	{
		SPI.endTransaction();
		SPI.end();
	}
		
	void SpiAdaptor::transfer(uint8_t* tx_data, ARG_OUT uint8_t* rx_data, uint8_t data_len)
	{
		for (uint8_t i = 0; i < data_len; i++)
			rx_data[i] = SPI.transfer(tx_data[i]);
	}
}