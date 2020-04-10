/*
 * OStream.cpp
 *
 * Created: 24/02/2019 12:19:01 PM
 *  Author: nbute
 */ 

#include "../../Shared/Data/OStream.h"
#include <stdio.h>
#include <string.h>

namespace BaseJumper
{
	const char* endl = "\n\r";

	 NullStream null_stream;

	 OStream& OStream::operator <<(const float val)
	 {
		 char str[20];
		 sprintf(str, "%.3f", val);
		 (*this) << str;	 
		 return *this;
	 }
	 
	OStream& OStream::operator <<(const uint8_t val)
	{
		char str[4];
		sprintf(str, "%u", val);
		(*this) << str;
		return *this;
	} 
	 
	OStream& OStream::operator <<(const uint16_t val)
	{
		char str[6];
		sprintf(str, "%u", val);
		(*this) << str;
		return *this;
	}
	
	/* clashes with existing operators on arduino. */
	#ifdef BASE
	OStream& OStream::operator <<(const size_t val)
	{
		return (*this) << static_cast<uint16_t>(val);
	}
	#endif

	OStream& OStream::operator <<(const uint32_t val)
	{
		char str[11];
		sprintf(str, "%u", val);
		(*this) << str;
		return *this;
	}
}
