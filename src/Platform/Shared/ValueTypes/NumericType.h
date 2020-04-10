/*
 * NumericType.h
 *
 * Created: 20/02/2019 9:27:56 PM
 *  Author: nbute
 */ 


#ifndef NUMERICTYPE_H_
#define NUMERICTYPE_H_

#include "ValueType.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

namespace BaseJumper
{
	template <class T>
	struct NumericType : public ValueType<T>
	{
		const char* const units;
		const T val_min;
		const T val_max;
	
		NumericType(const char* units_in, T min_in, T max_in) 
		: units(units_in), val_min(min_in), val_max(max_in)
		{
		}
	
		OStream& print_range(OStream& os) const override final
		{
			return (os << val_min << ".." << val_max << units);
		}
	
		bool check(T val) const override final
		{
			return (val >= val_min) && (val <= val_max);
		}
	
	};
}


#endif /* NUMERICTYPE_H_ */
