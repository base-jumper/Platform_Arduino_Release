#ifndef UINT16_H_INCLUDED
#define UINT16_H_INCLUDED

#include "ValueType.h"
#include "NumericType.h"

namespace BaseJumper
{
	struct Uint16Type : public NumericType<uint16_t>
	{
		Uint16Type(const char* units, uint16_t min, uint16_t max);
		OStream& print(OStream& os, const uint16_t val) const override;
		size_t parse(char* p_src, ARG_OUT bool& val_valid, ARG_OUT uint16_t& val) const override;
	};
}

#endif
