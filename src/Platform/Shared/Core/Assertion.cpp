/*
 * Assertion.cpp
 *
 * Created: 16/03/2020 10:24:46 AM
 *  Author: nbute
 */ 

#include "Assertion.h"

namespace BaseJumper
{
	bool debug_fail_flag = false;

	bool Assertion::assert(bool pass)
	{
		bool fail = !pass;
		
		if (fail)
		{
			// put break-point here if debugging.
			debug_fail_flag = true;
		}

		// update failed now
		auto failed_now_prev = failed_now;
		failed_now = fail;
		failed_now_changed = failed_now != failed_now_prev;
		
		// update failed ever
		auto failed_ever_prev = failed_ever;
		failed_ever = failed_ever || failed_now;
		failed_ever_changed = failed_ever != failed_ever_prev;
		
		// A task running at low-priority will take care of updating failed_ever
		// in storage and invoking the error handler. We don't do it here because
		// this function could be called from an ISR.
		
		return pass;
	}

	bool Assertion::assert_critical(bool pass)
	{
		if (!assert(pass))
		{
			while (1);
		}
		return false;
	}
}
