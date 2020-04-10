/* 
* InstructionInfo.h
*
* Created: 1/03/2019 12:33:46 PM
* Author: nbute
*/

#ifndef __INSTRUCTIONINFO_H__
#define __INSTRUCTIONINFO_H__

#include "../../Shared/ValueTypes/ValueType.h"
#include "../../Shared/ValueTypes/VoidType.h"
#include "../../Shared/Data/OStream.h"
#include "../../Shared/ValueTypes/Value.h"

namespace BaseJumper
{
	struct IInstructionInfo
	{
	public:
		const char* name;
		const uint8_t num_args;
		const bool has_return;
	
	protected:
		IInstructionInfo(const char* name_in, uint8_t num_args_in, bool has_return_in)
		: name(name_in), num_args(num_args_in), has_return(has_return_in)
		{
		}
		void operator =(const IInstructionInfo&) = delete;
		IInstructionInfo(IInstructionInfo& x) = delete;
	
	public:
		virtual const IValueType* const* get_arg_types() const 
		{
			return NULL;
		}
	
		virtual const IValueType* get_result_type() const
		{
			return NULL;
		}
	
		uint8_t total_arg_len() const
		{
			uint8_t len = 0;
			auto arg_types = get_arg_types();
			for (size_t i = 0; i < num_args; i++)
			{
				len += arg_types[i]->len;
			}
			return len;
		}
	
		uint8_t total_result_len() const
		{
			return (has_return ? get_result_type()->len : 0);
		}
	
		virtual OStream& print(OStream& os) const = 0;
	
		virtual OStream& print(OStream& os, const uint8_t* p_args, const uint8_t* p_result) const = 0;
		
		friend OStream& operator<<(OStream& os, const IInstructionInfo& ii)
		{
			return ii.print(os);
		}
	};
	
	template <class R>
	struct FuncInfo : public IInstructionInfo
	{
	
	  const ValueType<R>& result_type;
	
		public:
			FuncInfo(const char* p_name_in, ValueType<R>& result_type_in)
			: IInstructionInfo(p_name_in, 0, true),
			  result_type(result_type_in)
			{
			}
	
		const IValueType* get_result_type() const override final
		{
			return &result_type;
		}
	
		OStream& print(OStream& os) const override final
		{
			return os << this->name << "() = " << this->result_type;
		}
	
		OStream& print(OStream& os, R r) const
		{
			return os << this->name << "() = " << Value<R>(this->result_type,r);
		}
	
		OStream& print(OStream& os, const uint8_t* p_args, const uint8_t* p_result) const override final
		{
			R r = result_type.decode(p_result);
			return print(os,r);
		}
	};
	
	struct ActionInfo : public IInstructionInfo
	{
		public:
		ActionInfo(const char* p_name_in)
		: IInstructionInfo(p_name_in, 0, false)
		{
		}
		
		OStream& print(OStream& os) const override final
		{
			return os << name << "()";
		}
	
		virtual OStream& print(OStream& os, const uint8_t* p_args, const uint8_t* p_result) const override final
		{
			return print(os);
		}	
	};
	
	template <class A>
	struct Action1Info : public IInstructionInfo
	{
		const ValueType<A>* p_arg_type;
		const IValueType* const arg_types[1];
	
		public:
		Action1Info(const char* p_name_in, ValueType<A>& arg_type_in)
		: IInstructionInfo(p_name_in, 1, false), p_arg_type(&arg_type_in), arg_types { &arg_type_in }
		{
		}
	
		const IValueType* const* get_arg_types() const override final
		{
			return arg_types;
		}
	
		OStream& print(OStream& os, A a) const
		{
			return os << this->name << "(" << Value<A>(*this->p_arg_type,a) << ")";
		}
	
		OStream& print(OStream& os, const uint8_t* p_args, const uint8_t* p_result) const override final
		{
			A a = p_arg_type->decode(p_args);
			return print(os,a);
		}
	
		OStream& print(OStream& os) const override final
		{
			return os << this->name << "(" << *this->p_arg_type << ")";
		}
	};
	
	template <class A1, class A2>
	struct Action2Info : public IInstructionInfo
	{
		const ValueType<A1>& arg1_type;
		const ValueType<A2>& arg2_type;
		const IValueType* const arg_types[2];
	
		public:
		Action2Info(const char* p_name_in, ValueType<A1>& arg1_type_in, ValueType<A2>& arg2_type_in)
		: IInstructionInfo(p_name_in, 2, false), arg1_type(arg1_type_in), arg2_type(arg2_type_in), arg_types {&arg1_type_in, &arg2_type_in}
		{
		}
	
		const IValueType* const* get_arg_types() const override final
		{
			return arg_types;
		}
	
		void encode_args(A1 arg1, A2 arg2, ARG_OUT uint8_t* p_args) const
		{
			p_args += arg1_type.encode(arg1, p_args);
			arg2_type.encode(arg2, p_args);
		}

		void decode_args(const uint8_t* p_args, ARG_OUT A1& arg1, ARG_OUT A2& arg2) const
		{
			arg1 = arg1_type.decode(&p_args[0]);
			arg2 = arg2_type.decode(&p_args[arg1_type.len]);		
		}
	
		OStream& print(OStream& os, A1 arg1, A2 arg2) const
		{
			return os << this->name << "(" << Value<A1>(this->arg1_type,arg1) << ", " << Value<A2>(this->arg2_type,arg2) << ")";
		}
	
		OStream& print(OStream& os, const uint8_t* p_args, const uint8_t* p_result) const override final
		{
			A1 arg1;
			A2 arg2;
			decode_args(p_args,arg1,arg2);
			return print(os,arg1,arg2);
		}
	
		OStream& print(OStream& os) const override final
		{
			return os << this->name << "(" << arg1_type << ", " << arg2_type << ")";
		}
	};
}

#endif //__INSTRUCTIONINFO_H__
