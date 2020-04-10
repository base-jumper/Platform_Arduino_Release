#include "VoidType.h"
#include <string.h>

namespace BaseJumper
{
	VoidType VoidType::instance;
	
	VoidType::VoidType() : IValueType(0)
	{
	}
	
	OStream& VoidType::print_encoded(OStream& os, const uint8_t* p_encoded_val) const
	{
		return os << "void";
	}
	
	size_t VoidType::parse_encoded(char* p_src, ARG_OUT bool& val_valid, uint8_t* p_encoded_val) const
	{
	  val_valid = true;
	  return 0;
	}
	
	OStream& VoidType::print_range(OStream& os) const
	{
		return os << "void";
	}
	
	bool VoidType::check_encoded(uint8_t* encoded_val) const
	{
		return true;
	}
}
