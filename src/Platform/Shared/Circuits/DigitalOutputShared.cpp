#include "../../Shared/Circuits/DigitalOutputShared.h"
#include "../../Shared/ValueTypes/CommonTypes.h"

namespace BaseJumper
{
	namespace DigitalOutput
	{
		/* Value Types */
		TristateEnum state_type;
		const char* status_state_names[] = { "ok", "overload shutdown" };
		EnumType<Status> status_type(status_state_names, 2);
	
		/* Instructions */
		Action1Info<Tristate> set_state_info("set_state",state_type);
		FuncInfo<Status> get_status_info("get_status",status_type);
		ActionInfo reset_status_info("reset_status");
	}
}
