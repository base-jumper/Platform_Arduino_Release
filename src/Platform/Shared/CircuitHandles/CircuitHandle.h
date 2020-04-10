#ifndef CIRCUITHANDLE_H_INCLUDED
#define CIRCUITHANDLE_H_INCLUDED

#include "../../Shared/SharedCommon.h"
#include "../../Shared/ClientServer/InstructionInfo.h"
#include "../../Shared/Circuits/GeneralShared.h"
#include "../../Shared/Clients/Client.h"

namespace BaseJumper
{
	constexpr uint8_t direct_board_id = 0xFD;
	extern Client& default_client;
	
	class CircuitHandle : General::Interface
	{
	  private:
	    const uint8_t board_id;
	    const Circuit::Type circuit_type;
	    const Circuit::CircuitNum circuit_num;
	    Client& client;
	
	  protected:
	    CircuitHandle(uint8_t board, Circuit::Type circuit_type, Circuit::CircuitNum circuit_num, Client& client = default_client);
		CircuitHandle(Circuit::Type circuit_type, Circuit::CircuitNum circuit_num, Client& client = default_client);
		CircuitHandle(Circuit::Type circuit_type, Client& client = default_client);
		
		template <class R> 
		R request_func(Circuit::InstructionNum instruction, FuncInfo<R>& instruction_info)
		{
			auto& result_type = instruction_info.result_type;
			Header header(board_id, circuit_type, circuit_num, instruction, 0, result_type.len);
			uint8_t args[0];
			uint8_t result[result_type.len];
			client.send_command(header, args, result);
			return result_type.decode(result);
		}
	
		void request_action(Circuit::InstructionNum instruction, ActionInfo& instruction_info)
		{
			Header header(board_id, circuit_type, circuit_num, instruction, 0, 0);
			uint8_t args[0];
			uint8_t result[0];
			client.send_command(header, args, result);
		}
	
		template <class A>
		void request_action1(Circuit::InstructionNum instruction, Action1Info<A>& instruction_info, A arg)
		{
			auto& arg_type = *instruction_info.p_arg_type;
			Header header(board_id, circuit_type, circuit_num, instruction, arg_type.len, 0);
			uint8_t args[arg_type.len];
			uint8_t result[0];
			arg_type.encode(arg, args);
			client.send_command(header, args, result);
		}
	
		template <class A1, class A2>
		void request_action2(Circuit::InstructionNum instruction, Action2Info<A1,A2>& instruction_info, A1 arg1, A2 arg2)
		{
			auto args_len = instruction_info.total_arg_len();
			Header header(board_id, circuit_type, circuit_num, instruction, args_len, 0);
			uint8_t args[args_len];
			uint8_t result[0];
			instruction_info.encode_args(arg1,arg2,args);
			client.send_command(header, args, result);
		}

	  public:
	    void create() override final;
	    void destroy() override final;
	    bool created() override final;
	};
}

#endif //CIRCUITHANDLE_H_INCLUDED
