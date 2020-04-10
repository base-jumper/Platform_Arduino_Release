#include "Uint32Type.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

namespace BaseJumper
{

	Uint32Type::Uint32Type(const char* units, uint32_t min, uint32_t max)
	: NumericType(units, min, max)
	{

	}

	OStream& Uint32Type::print(OStream& os, const uint32_t val) const
	{
		return os << val;
	}

	size_t Uint32Type::parse(char* p_src, ARG_OUT bool& val_valid, ARG_OUT uint32_t& val) const
	{
	  auto p = p_src;
	  while (isdigit(*p)) 
		p++;
	  uint32_t n = p - p_src;
	  if (n > 0)
	  {
		val_valid = true;
		val = atol(p_src);
	  }
	  else
	  {
		val_valid = false;
	  }
	  return n;
	}
}
