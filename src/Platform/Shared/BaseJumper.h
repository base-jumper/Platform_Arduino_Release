/* API between application and base jumper circuits
 * #include this header in the application to access all the circuits
 * The same API applies to application running on a platform or on the baseboard 
 * itself.
 */

#ifndef BASEJUMPER_H_INCLUDED
#define BASEJUMPER_H_INCLUDED

#include "../Shared/CircuitHandles/LedHandle.h"
#include "../Shared/CircuitHandles/DigitalOutputHandle.h"
#include "../Shared/CircuitHandles/DigitalInputHandle.h"
#include "../Shared/CircuitHandles/SerialPortHandle.h"

namespace BaseJumper
{
	void basejumper_init();
	void basejumper_register_exception_handler(Client::ExceptionHandler exception_handler_fptr);
}

#endif
