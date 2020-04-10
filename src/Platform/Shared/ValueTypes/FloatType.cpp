/*
 * FloatType.cpp
 *
 * Created: 19/02/2019 6:53:55 PM
 *  Author: nbute
 */ 

#include "FloatType.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

namespace BaseJumper
{
	FloatType::FloatType(char* units, float min, float max)
	: NumericType(units,min,max)
	{
	
	}
	
	 OStream& FloatType::print(OStream& os, const float val) const
	 {
		 return os << val;
	 }
	
	 size_t FloatType::parse(char* p_src, ARG_OUT bool& val_valid, ARG_OUT float& val) const
	 {
		 char* p = p_src;
		 
		 // determine where number ends
		 bool first_char = true;
		 bool seen_dp = false;
		 while ((first_char && ((*p == '-') || (*p == '+'))) || // can start with a + or -
			    isdigit(*p) || // must contain digits
		        ((*p == '.') && (!seen_dp))) // can contain up to one decimal point
		 {
			first_char = false;
			seen_dp = (*p == '.');
			p++;
		 }
		 
		 // The last character shouldn't be a decimal point or a sign
		 char last = *(p - 1);
		 if ((last == '.') || (last == '+') || (last == '-'))
			p--;
	
		 uint16_t n = p - p_src;
	
		 if (n > 0)
		 {
			val_valid = true;
			val = atof(p_src);
		 }
		 else
		 {
			val_valid = false;
		 }
		 return n;
	 }
}
