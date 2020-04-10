/* 
* SystemClient.h
*
* Created: 29/06/2019 8:57:10 PM
* Author: nbute
*/


#ifndef __SYSTEMHANDLE_H__
#define __SYSTEMHANDLE_H__

#include "../../Shared/Circuits/SystemShared.h"
#include "../../Shared/CircuitHandles/CircuitHandle.h"

namespace BaseJumper
{
	namespace System
	{
		class Handle : public Interface, public CircuitHandle
		{
			public:
				Handle(uint8_t board_id, Client& client);
				Handle(uint8_t board_id = Board_Local);
				void faults() override final;
				void clear_faults() override final;		
				void set_dummy_fault() override final;
				void reset_dummy_fault() override final;
				void circuits() override final;
				uint8_t get_board_id() override final;
				void set_board_id(uint8_t id) override final;
		};
	}
}
#endif //__SYSTEMHANDLE_H__
