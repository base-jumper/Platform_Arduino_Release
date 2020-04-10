#ifndef UNIT_H_INCLUDED
#define UNIT_H_INCLUDED

#include "../../Shared/SharedCommon.h"
#include <stdio.h>
#include <string.h>
//#include "Core/Context.h"
#include "../../Shared/Data/OStream.h"

namespace BaseJumper
{
	struct IValueType
	{
	    const size_t len;
	
		IValueType(size_t len_in) : len(len_in) {};
		virtual OStream& print_encoded(OStream& os, const uint8_t* p_encoded_val) const = 0;
	    virtual size_t parse_encoded(char* p_src, ARG_OUT bool& val_valid, ARG_OUT uint8_t* p_encoded_val) const = 0;
		virtual OStream& print_range(OStream& os) const = 0;
		virtual bool check_encoded(uint8_t* encoded_val) const = 0;
	
		friend OStream& operator<<(OStream& os, const IValueType& vt)
		{
			return vt.print_range(os);
		}
	};
	
	template<class T> struct ValueType : public IValueType
	{
	  ValueType(size_t len_in = sizeof(T)) : IValueType(len_in) {};
	
	  virtual uint16_t encode(T src, uint8_t* p_dest) const
	  {
	    memcpy(p_dest,  &src, sizeof(T));
	    return len;
	  }
	  
	  virtual T decode(const uint8_t* p_src) const
	  {
	    T* p = const_cast<T*>(reinterpret_cast<const T*>(p_src));
		return *p;
		//return static_cast<T>(*p_src);
	  }
	
	  template <class U> U decode(const uint8_t* p_src) const
	  {
	    return static_cast<U>(*p_src);
	  }
	
	  virtual OStream& print(OStream& os, const T val) const = 0;
	
	  OStream& print_encoded(OStream& os, const uint8_t* p_encoded_val) const override final
	  {
		return print(os, decode(p_encoded_val));
	  }
	
	  virtual size_t parse(char* p_src, ARG_OUT bool& val_valid, ARG_OUT T& val) const = 0;
	
	  size_t parse_encoded(char* p_src, ARG_OUT bool& val_valid, ARG_OUT uint8_t* p_encoded_val) const override final
	  {
		T v;
		auto len = parse(p_src, val_valid, v);
		if (val_valid)
			encode(v, p_encoded_val);
		return len;
	  }
	
	  virtual bool check(T val) const = 0;
	
	  bool check_encoded(uint8_t* encoded_val) const override final
	  {
		return check(decode(encoded_val));
	  }
	};
}

#endif
