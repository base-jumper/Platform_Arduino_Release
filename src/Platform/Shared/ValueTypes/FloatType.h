/*
 * FloatType.h
 *
 * Created: 19/02/2019 6:54:14 PM
 *  Author: nbute
 */ 


#ifndef FLOATTYPE_H_
#define FLOATTYPE_H_

#include "ValueType.h"
#include "NumericType.h"

namespace BaseJumper
{
	struct FloatType : public NumericType<float>
	{
	  FloatType(char* units, float min, float max);
	  OStream& print(OStream& os, const float val) const override;
	  size_t parse(char* p_src, ARG_OUT bool& val_valid, ARG_OUT float& val) const override;	
	};
}


#endif /* FLOATTYPE_H_ */
