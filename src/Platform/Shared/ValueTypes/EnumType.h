#ifndef ENUM_H_INCLUDED
#define ENUM_H_INCLUDED

#include "ValueType.h"

namespace BaseJumper
{
	template <class T>
	struct EnumType : public ValueType<T>
	{
	  const char** state_names;
	  const uint8_t num_states;
	  
	  EnumType(const char** state_names_in, const uint8_t num_states_in) 
	  : ValueType<T>(sizeof(uint8_t)), state_names(state_names_in), num_states(num_states_in)
	  {
	
	  }
	   
		OStream& print(OStream& os, const T val) const override
		{
			return os << state_names[val];
		}  
	  
		size_t parse(char* p_src, ARG_OUT bool& val_valid, ARG_OUT T& val) const override
		{
			for (uint8_t i = 0; i < num_states; i++)
			{
				auto name = state_names[i];
				if (strncmp(name, p_src, strlen(name)) == 0)
				{
					val_valid = true;
					val = static_cast<T>(i);
					return strlen(name);
				}
			}
			val_valid  = false;
			return 0;
		}
	   
		OStream& print_range(OStream& os) const override
		{
			for (uint8_t i = 0; i < num_states; i++)
			{
				print(os, static_cast<T>(i));
				if (i+2 < num_states)
					os << ", ";
				else if (i+2 == num_states)
					os << " or ";
			}
			return os;
		}  
	  
		bool check(T val) const override
		{
			return (val >= 0) && (val < num_states);
		}
	
	  virtual uint16_t encode(T src, uint8_t* p_dest) const override
	  {
		  // treat enum's as Uint8
		  uint8_t v = src;
		  memcpy(p_dest,  &v, sizeof(v));
		  return this->len;
	  }
	  
	  virtual T decode(const uint8_t* p_src) const override
	  {
		  // treat enum's as Uint8
		  uint8_t v = *const_cast<T*>(reinterpret_cast<const T*>(p_src));
		  return static_cast<T>(v);
	  }
	};
}

#endif
