#include "BoolType.h"
#include <string.h>

namespace BaseJumper
{
	OStream& BoolType::print(OStream& os, const bool val) const
	{
		return os << (val ? "true" : "false");
	}
	
	size_t BoolType::parse(char* p_src, ARG_OUT bool& valid, ARG_OUT bool& val) const
	{
	  if (strncmp(p_src, "high", 4) == 0)
	  {
	    valid = true;
		val = true;
	    return 4;
	  }
	  if (strncmp(p_src, "low", 3) == 0)
	  {
	    valid = true;
		val = false;
	    return 3;
	  }
	  if (strncmp(p_src, "false", 5) == 0)
	  {
	    valid = true;
		val = false;
	    return 5;
	  }
	  if (strncmp(p_src, "true", 4) == 0)
	  {
	    valid = true;
		val = true;
	    return 4;
	  }
	  if (strncmp(p_src, "t", 1) == 0)
	  {
	    valid = true;
		val= true;
	    return 1;
	  }
	  if (strncmp(p_src, "f", 1) == 0)
	  {
	    valid = true;
		val = false;
	    return 1;  
	  }
	  if (strncmp(p_src, "1", 1) == 0)
	  {
	    valid = true;
		val = true;
	    return 1;  
	  }  
	  if (strncmp(p_src, "0", 1) == 0)
	  {
	    valid = true;
		val = false;
	    return 1;  
	  }
	  valid = false;
	  return 0;
	}
	
	OStream& BoolType::print_range(OStream& os) const
	{
		return os << "true or false";
	}
	
	bool BoolType::check(bool val) const
	{
		return true;
	}
}
