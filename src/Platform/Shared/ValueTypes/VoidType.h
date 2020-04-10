#ifndef VOID_H_INCLUDED
#define VOID_H_INCLUDED

#include "ValueType.h"

namespace BaseJumper
{
	struct VoidType : public IValueType
	{
		static VoidType instance;
		VoidType();
		OStream& print_encoded(OStream& os, const uint8_t* p_encoded_val) const override final;
		size_t parse_encoded(char* p_src, ARG_OUT bool& val_valid, uint8_t* p_encoded_val) const override final;
		OStream& print_range(OStream& os) const override final;
		bool check_encoded(uint8_t* encoded_val) const override final;
	};
}

#endif
