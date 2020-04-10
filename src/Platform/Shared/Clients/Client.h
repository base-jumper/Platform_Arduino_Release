#ifndef ICLIENT_H_INCLUDED
#define ICLIENT_H_INCLUDED

#include "../../Shared/SharedCommon.h"
#include "../../Shared/ClientServer/Header.h"
#include "../../Shared/ClientServer/Exception.h"
#include "../../Shared/ClientServer/InstructionInfo.h"

namespace BaseJumper
{
	class Client
	{
	  public:
	    struct Exception
	    {
	      static constexpr uint8_t max_command_print_len = 200; //TODO move
		  static constexpr uint16_t max_print_len = ExceptionData::max_print_len + max_command_print_len + 4;
	  
	      Client& client;
	      Header header;
	      ExceptionData exception_data;
	
	      Exception();
	      Exception(Client& client, Header header, ExceptionData exception_data);
	      size_t print(char* p_dest) const;
	    };
	
		typedef void (*ExceptionHandler)(Exception e);
	
	  private:
		ExceptionHandler handler_fptr;
	
	  protected:
	    Client(ExceptionHandler handler_fptr_in);
	    virtual ExceptionData send_command_impl(Header header, const uint8_t* p_args, ARG_OUT uint8_t* p_result) = 0;
		void invalidate_result(uint8_t* p_result, uint8_t result_len);
	
	
	  public:
	    virtual void init();
		virtual void deinit();
	    virtual void send_command(Header header, const uint8_t* p_args, ARG_OUT uint8_t* p_result);
	};
}

#endif //ICLIENT_H_INCLUDED
