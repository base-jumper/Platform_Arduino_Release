#ifndef EXCEPTION_H_INCLUDED
#define EXCEPTION_H_INCLUDED

#include "../../Shared/SharedCommon.h"
#include "../../Shared/ClientServer/CircuitDefinitions.h"
#include "../../Shared/ClientServer/InstructionInfo.h"
#include "../../Shared/Data/OStream.h"

/* Exception Data */

namespace BaseJumper
{
	constexpr char read_success_code = 0x00;
	constexpr char write_success_code = 0x00;
	
	struct ExceptionData {
		typedef enum
		{
			/* In ascending order by priority */
			// no priority: all good
			Code_None,
			// low priority: can still respond to command
			Code_CircuitNotCreated,
			Code_CircuitNumberInvalid,
			Code_ResourceConflict,
			Code_BoardInvalid,
			// high priority: cannot respond to command (command instruction entries not accessible)
			Code_DataLenInvalid,
			Code_InstructionInvalid,
			Code_CircuitTypeInvalid,
			Code_ArgumentsLengthInvalid,
			Code_ProtocolError,
			Code_Unresolvable = 0xFF
		} Code;
	
		static constexpr uint8_t size = 4;
		static constexpr uint8_t high_priority_threshold = Code_InstructionInvalid;
		static constexpr uint16_t max_print_len = 100;
	
		Code code;
		uint8_t args[size-1];
	
		static ExceptionData none();
		static ExceptionData circuit_number_invalid(uint8_t num_circuits);
		static ExceptionData resource_conflict(Circuit::Type circuit, Circuit::CircuitNum num);
		static ExceptionData circuit_type_invalid();
		static inline ExceptionData data_len_invalid(uint8_t actual, uint8_t expected);
		static ExceptionData instruction_invalid(uint8_t instruction);
		static ExceptionData arguments_length_invalid(uint8_t received_args_len, uint8_t expected_args_len);
		static ExceptionData circuit_not_created();
		static ExceptionData protocol_error();
		static ExceptionData board_invalid();
	
		static ExceptionData highest_priority(ExceptionData e1, ExceptionData e2);
		static ExceptionData decode(uint8_t* p_data);
	  
		bool is_none();
		bool is_high_priority();
		OStream& print(OStream& os) const;
		void encode(uint8_t* p_dest);
	
		friend OStream& operator<<(OStream& os, const ExceptionData& e)
		{
			return e.print(os);
		}
	};
	
	inline ExceptionData ExceptionData::none()
	{
	  return 
	    ExceptionData {
	      .code = Code_None,
	      .args = {0,0,0}
	      };
	}
	
	inline ExceptionData ExceptionData::circuit_number_invalid(uint8_t num_circuits)
	{
	  return 
	    ExceptionData {
	      .code = Code_CircuitNumberInvalid,
	      .args = {num_circuits,0,0}
	      };
	}
	
	inline ExceptionData ExceptionData::resource_conflict(Circuit::Type circuit, Circuit::CircuitNum num)
	{
	  return 
	    ExceptionData {
	      .code = Code_ResourceConflict,
	      .args = {circuit,num,0}
	      };
	}
	
	inline ExceptionData ExceptionData::circuit_not_created()
	{
	  return 
	    ExceptionData {
	      .code = Code_CircuitNotCreated,
	      .args = {0,0,0}
	      };
	}
	
	inline ExceptionData ExceptionData::board_invalid()
	{
	  return 
	    ExceptionData {
	      .code = Code_BoardInvalid,
	      .args = {0,0,0}
	      };
	}
	
	inline ExceptionData ExceptionData::circuit_type_invalid()
	{
	  return 
	    ExceptionData {
	      .code = Code_CircuitTypeInvalid,
	      .args = {0,0,0}
	      };
	}
	
	inline ExceptionData ExceptionData::instruction_invalid(uint8_t instruction)
	{
	  return 
	    ExceptionData {
	      .code = Code_InstructionInvalid,
	      .args = {instruction,0,0}
	      };
	}
	
	inline ExceptionData ExceptionData::data_len_invalid(uint8_t actual, uint8_t expected)
	{
		return
		ExceptionData {
			.code = Code_DataLenInvalid,
			.args = {static_cast<uint8_t>(actual),static_cast<uint8_t>(expected),0}
		};
	}
	
	inline ExceptionData ExceptionData::arguments_length_invalid(uint8_t received_args_len, uint8_t expected_args_len)
	{
	  return 
	    ExceptionData {
	      .code = Code_ArgumentsLengthInvalid,
	      .args = {received_args_len,expected_args_len,0}
	      };
	}
	
	inline ExceptionData ExceptionData::protocol_error()
	{
	  return 
	    ExceptionData {
	      .code = Code_ProtocolError,
	      .args = {0,0,0}
	      };
	}
	
	inline ExceptionData ExceptionData::decode(uint8_t* p_data)
	{
	  return
	    ExceptionData {
	      .code = static_cast<ExceptionData::Code>(p_data[0]),
	      .args = { p_data[1], p_data[2], p_data[3] }
	    };
	}
	
	inline bool ExceptionData::is_none()
	{
	  return code == Code_None;
	}
}

#endif //EXCEPTION_H_INCLUDED
