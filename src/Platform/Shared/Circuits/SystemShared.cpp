/* 
* SystemShared.cpp
*
* Created: 29/06/2019 8:06:12 PM
* Author: nbute
*/


#include "SystemShared.h"

namespace BaseJumper
{
	namespace System
	{
		/* Value Types */
		Uint8Type board_id_type("", 1, 0xFE);

		/* Instructions */
		ActionInfo faults_info("faults");
		ActionInfo clear_faults_info("clear_faults");
		ActionInfo set_dummy_fault_info("set_dummy_fault");
		ActionInfo reset_dummy_fault_info("reset_dummy_fault");
		ActionInfo circuits_info("circuits");
		Action1Info<uint8_t> set_board_id_info("set_board_id", board_id_type);
		FuncInfo<uint8_t> get_board_id_info("get_board_id", board_id_type);
	}
}
