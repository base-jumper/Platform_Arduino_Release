#ifndef UINT8_H_INCLUDED
#define UINT8_H_INCLUDED

#include "ValueType.h"
#include "NumericType.h"

namespace BaseJumper
{
	struct Uint8Type : public NumericType<uint8_t>
	{
	  Uint8Type(const char* units, uint8_t min, uint8_t max);
	  OStream& print(OStream& os, const uint8_t val) const override;
	  size_t parse(char* p_src, ARG_OUT bool& val_valid, ARG_OUT uint8_t& val) const override;
	};
}

#endif
