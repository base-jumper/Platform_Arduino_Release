/*
 * InstructionResult.h
 *
 * Created: 23/04/2019 8:06:36 PM
 *  Author: nbute
 */ 


#ifndef INSTRUCTIONRESULT_H_
#define INSTRUCTIONRESULT_H_

#include "../../Shared/ClientServer/InstructionInfo.h"
#include "../../Shared/ClientServer/Exception.h"

namespace BaseJumper
{
	struct InstructionResult
	{
		const IInstructionInfo& info;
	
		InstructionResult(const IInstructionInfo& info_in)
		: info(info_in)
		{
	
		}
	
		virtual OStream& print(OStream&) const = 0;
	
		friend OStream& operator<<(OStream& os, const InstructionResult& ir)
		{
			return ir.print(os);
		}
	};
	
	struct InstructionSuccess : public InstructionResult
	{
		const uint8_t* p_args; 
		const uint8_t* p_result; 
	
		InstructionSuccess(const IInstructionInfo& info_in, const uint8_t* p_args_in, const uint8_t* p_result_in) 
		: InstructionResult(info_in), p_args(p_args_in), p_result(p_result_in)
		{
	
		}
	
		virtual OStream& print(OStream& os) const override final
		{
			return this->info.print(os, p_args, p_result);
		}
	};
	
	struct InstructionFail : public InstructionResult
	{
		const ExceptionData e;
	
		InstructionFail(const IInstructionInfo& info_in, ExceptionData e_in)
		: InstructionResult(info_in), e(e_in)
		{
	
		}
	
		virtual OStream& print(OStream& os) const override final
		{
			return os << this->info.name << " threw exception: " << e;
		}
	};
}

#endif /* INSTRUCTIONRESULT_H_ */
