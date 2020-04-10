#include "SerialPortShared.h"

namespace BaseJumper
{
	namespace SerialPort
	{
		/* Value Types */
		Uint8Type u8("",0,255); // TODO: replace with byte type which displays as hex or chars.
		ArrayType<uint8_t,8> array8_uint8_type(u8);
		Uint16Type uint16_type("bytes",0,UINT16_MAX);
		Uint32Type baud_type("bit/s",9600,115200);
		const char* state_names[] = { "5N1", "6N1", "7N1", "8N1", "5N2", "6N2", "7N2", "8N2", "5E1", "6E1", "7E1", "8E1", "5E2", "6E2", "7E2", "8E2", "5O1", "6O1", "7O1", "8O1", "5O2", "6O2", "7O2", "8O2" }; 
		EnumType<SerialPort::Config> config_type(state_names, 23);
	
		/* Instructions */
		Action2Info<uint32_t,SerialPort::Config> start_info("start", baud_type, config_type);
		FuncInfo<uint16_t> available_info("available", uint16_type);
		FuncInfo<uint8_t> read_info("read", u8);
		FuncInfo<Array<uint8_t,8>> read8_info("read8", array8_uint8_type);
		Action1Info<uint8_t> write_info("write", u8);
		Action1Info<Array<uint8_t,8>> write8_info("write8", array8_uint8_type);
		ActionInfo clear_info("clear");
	}
}
