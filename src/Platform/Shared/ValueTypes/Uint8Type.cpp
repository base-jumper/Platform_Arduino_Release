#include "Uint8Type.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

namespace BaseJumper
{
	Uint8Type::Uint8Type(const char* units, uint8_t min, uint8_t max)
	: NumericType(units,min,max)
	{
	}
	
	OStream& Uint8Type::print(OStream& os, const uint8_t val) const
	{
		return os << val;
	}
	
	
	size_t Uint8Type::parse(char* p_src, ARG_OUT bool& val_valid, ARG_OUT uint8_t& val) const
	{
	  auto p = p_src;
	  while (isdigit(*p)) 
	    p++;
	  size_t n = p - p_src;
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
