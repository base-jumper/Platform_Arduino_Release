#include "../../Shared/CircuitHandles/CircuitHandle.h"
#include "../../Shared/ClientServer/Header.h"
#include <string.h>

namespace BaseJumper
{
	using namespace General;
	
	CircuitHandle::CircuitHandle(uint8_t board_id_in, Circuit::Type circuit_type_in, Circuit::CircuitNum circuit_num_in, Client& client_in)
	  : board_id(board_id_in), circuit_type(circuit_type_in), circuit_num(circuit_num_in), client(client_in)
	{
	}
	
	CircuitHandle::CircuitHandle(Circuit::Type circuit_type_in, Circuit::CircuitNum circuit_num_in, Client& client_in)
	: CircuitHandle(Board_Local, circuit_type_in, circuit_num_in, client_in)
	{
	}
	
	CircuitHandle::CircuitHandle(Circuit::Type circuit_type_in, Client& client_in)
	: CircuitHandle(Board_Local, circuit_type_in, 0, client_in)
	{
	}
	
	void CircuitHandle::create()
	{
	  request_action(Instruction_Create, create_info);
	}
	
	void CircuitHandle::destroy()
	{
		request_action(Instruction_Destroy, destroy_info);
	}
	
	bool CircuitHandle::created()
	{
	  return request_func<bool>(Instruction_Created, created_info);
	}
}
