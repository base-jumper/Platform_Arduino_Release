/* 
* TristateEnum.cpp
*
* Created: 27/02/2019 9:42:28 PM
* Author: nbute
*/


#include "TristateEnum.h"

namespace BaseJumper
{
	static const char* tristate_state_names[3] = { "high-z", "high", "low" };
	
	TristateEnum::TristateEnum() 
	: EnumType(tristate_state_names, 3)
	{
	
	}
}
