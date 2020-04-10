#ifndef BOOL_H_INCLUDED
#define BOOL_H_INCLUDED

#include "ValueType.h"

namespace BaseJumper
{
	struct BoolType : public ValueType<bool>
	{
	  OStream& print(OStream& os, const bool val) const override final;
	  size_t parse(char* p_src, ARG_OUT bool& val_valid, ARG_OUT bool& val) const override final;
	  OStream& print_range(OStream& os) const override final;
	  bool check(bool val) const override final;
	};
}

#endif
