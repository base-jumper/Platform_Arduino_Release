#ifndef UINT32_H_INCLUDED
#define UINT32_H_INCLUDED

#include "ValueType.h"
#include "NumericType.h"

namespace BaseJumper
{
	struct Uint32Type : public NumericType<uint32_t>
	{
		Uint32Type(const char* units, uint32_t min, uint32_t max);
		OStream& print(OStream& os, const uint32_t val) const override;
		size_t parse(char* p_src, ARG_OUT bool& val_valid, ARG_OUT uint32_t& val) const override;
	};
}

#endif
