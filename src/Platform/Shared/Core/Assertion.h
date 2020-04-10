/*
 * Assertion.h
 *
 * Created: 16/03/2020 10:24:34 AM
 *  Author: nbute
 */ 


#ifndef ASSERTION_H_
#define ASSERTION_H_

#include "../../Shared/SharedCommon.h"

namespace BaseJumper
{
	struct Assertion
	{
		uint32_t class_id : 8;
		uint32_t instance_id : 8;
		uint32_t local_id : 8;
		uint32_t failed_now : 1;
		uint32_t failed_ever : 1;
		uint32_t failed_now_changed : 1;
		uint32_t failed_ever_changed : 1;

		bool assert(bool pass);
		bool assert_critical(bool pass);
	};
}

#endif /* ASSERTION_H_ */
