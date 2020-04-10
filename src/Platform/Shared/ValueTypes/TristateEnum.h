/* 
* TristateEnum.h
*
* Created: 27/02/2019 9:42:28 PM
* Author: nbute
*/


#ifndef __TRISTATEENUM_H__
#define __TRISTATEENUM_H__

#include "../../Shared/ValueTypes/EnumType.h"

namespace BaseJumper
{
	enum Tristate
	{
		State_HighZ,
		State_High,
		State_Low
	};
	
	struct TristateEnum : public EnumType<Tristate>
	{
		TristateEnum();
	}; 
}

#endif //__TRISTATEENUM_H__
