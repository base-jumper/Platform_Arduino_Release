#include "../../Shared/Circuits/DigitalInputShared.h"
#include "../../Shared/ValueTypes/CommonTypes.h"

namespace BaseJumper
{
	namespace DigitalInput
	{
		/* Value Types */
		BoolType state_type;
	
		/* Instructions */
		FuncInfo<bool> get_state_info("get_state",state_type);
	}
}
