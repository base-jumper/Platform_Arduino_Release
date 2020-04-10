#ifndef ISPI_H_INCLUDED
#define ISPI_H_INCLUDED

#include "../PlatformCommon.h"

namespace BaseJumper
{
	class ISpi
	{
	  public:
		virtual void init() = 0;
		virtual void deinit() = 0;
	
	    virtual uint8_t transfer(uint8_t tx)
		{
			uint8_t rx;
			transfer(&tx,&rx,1);
			return rx;
		}
	
	    virtual void transfer(uint8_t* p_tx, uint8_t* p_rx, uint8_t data_len) = 0;
	};
}

#endif
