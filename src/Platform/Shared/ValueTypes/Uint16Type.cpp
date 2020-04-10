#include "Uint16Type.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

namespace BaseJumper
{
	Uint16Type::Uint16Type(const char* units, uint16_t min, uint16_t max)
	: NumericType(units, min, max)
	{
	
	}
	
	OStream& Uint16Type::print(OStream& os, const uint16_t val) const
	{
		return os << val;
	}
	
	size_t Uint16Type::parse(char* p_src, ARG_OUT bool& val_valid, ARG_OUT uint16_t& val) const
	{
	  auto p = p_src;
	  while (isdigit(*p)) 
	    p++;
	  uint16_t n = p - p_src;
	  if (n > 0)
	  {
	    val_valid = true;
		val = atoi(p_src);
	  }
	  else
	  {
		val_valid = false;
	  }
	  return n;
	}
}
