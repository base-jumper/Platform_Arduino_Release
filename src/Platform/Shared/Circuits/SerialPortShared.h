#ifndef __SERIALSHARED_H__
#define __SERIALSHARED_H__

#include "../../Shared/SharedCommon.h"
#include "../../Shared/ClientServer/InstructionInfo.h"
#include "../../Shared/ValueTypes/CommonTypes.h"

namespace BaseJumper
{
	namespace SerialPort
	{
		/* Macros */
		#define CONFIG_ENCODE(CHARLEN,PARITY,STOPBITS) (CHARLEN | (PARITY << 2) | (STOPBITS << 4))
		#define CONFIG_DECODE_CHARLEN(ENUM) (static_cast<CharLen>(ENUM & 0x0003))
		#define CONFIG_DECODE_PARITY(ENUM) (static_cast<Parity>((ENUM >> 2) & 0x0003))
		#define CONFIG_DECODE_STOPBITS(ENUM) (static_cast<StopBits>((ENUM >> 4) & 0x0001))
	
		/* Types */
		enum Parity
		{
			Parity_None,
			Parity_Even,
			Parity_Odd
		};
	
		enum StopBits
		{
			StopBits_1,
			StopBits_2
		};
	
		enum Endian
		{
			Endian_Small, // LSB is sent first
			Endian_Big    // MSB is sent first
		};
	
		enum CharLen
		{
			CharLen_5,
			CharLen_6,
			CharLen_7,
			CharLen_8
		};
	
		enum Config
		{
			Config_5N1 = CONFIG_ENCODE(CharLen_5, Parity_None, StopBits_1),
			Config_6N1 = CONFIG_ENCODE(CharLen_6, Parity_None, StopBits_1),
			Config_7N1 = CONFIG_ENCODE(CharLen_7, Parity_None, StopBits_1),
			Config_8N1 = CONFIG_ENCODE(CharLen_8, Parity_None, StopBits_1),
			Config_5N2 = CONFIG_ENCODE(CharLen_5, Parity_None, StopBits_2),
			Config_6N2 = CONFIG_ENCODE(CharLen_6, Parity_None, StopBits_2),
			Config_7N2 = CONFIG_ENCODE(CharLen_7, Parity_None, StopBits_2),
			Config_8N2 = CONFIG_ENCODE(CharLen_8, Parity_None, StopBits_2),
			Config_5E1 = CONFIG_ENCODE(CharLen_5, Parity_Even, StopBits_1),
			Config_6E1 = CONFIG_ENCODE(CharLen_6, Parity_Even, StopBits_1),
			Config_7E1 = CONFIG_ENCODE(CharLen_7, Parity_Even, StopBits_1),
			Config_8E1 = CONFIG_ENCODE(CharLen_8, Parity_Even, StopBits_1),
			Config_5E2 = CONFIG_ENCODE(CharLen_5, Parity_Even, StopBits_2),
			Config_6E2 = CONFIG_ENCODE(CharLen_6, Parity_Even, StopBits_2),
			Config_7E2 = CONFIG_ENCODE(CharLen_7, Parity_Even, StopBits_2),
			Config_8E2 = CONFIG_ENCODE(CharLen_8, Parity_Even, StopBits_2),
			Config_5O1 = CONFIG_ENCODE(CharLen_5, Parity_Odd, StopBits_1),
			Config_6O1 = CONFIG_ENCODE(CharLen_6, Parity_Odd, StopBits_1),
			Config_7O1 = CONFIG_ENCODE(CharLen_7, Parity_Odd, StopBits_1),
			Config_8O1 = CONFIG_ENCODE(CharLen_8, Parity_Odd, StopBits_1),
			Config_5O2 = CONFIG_ENCODE(CharLen_5, Parity_Odd, StopBits_2),
			Config_6O2 = CONFIG_ENCODE(CharLen_6, Parity_Odd, StopBits_2),
			Config_7O2 = CONFIG_ENCODE(CharLen_7, Parity_Odd, StopBits_2),
			Config_8O2 = CONFIG_ENCODE(CharLen_8, Parity_Odd, StopBits_2)
		};
	
		/* Instruction Enum */
		typedef enum
		{
			Instruction_Start,
			Instruction_Available,
			Instruction_Read,
			Instruction_Read8,
			Instruction_Write,
			Instruction_Write8,
			Instruction_Clear,
			Num_Instructions
		} Instruction;
	
		/* Value Types */
		extern ArrayType<uint8_t,8> array8_uint8_type;
		extern Uint32Type baud_type;
		extern EnumType<SerialPort::Config> config_type;
	
		/* Instructions */
		extern Action2Info<uint32_t, SerialPort::Config> start_info;
		extern FuncInfo<uint16_t> available_info;
		extern FuncInfo<uint8_t> read_info;
		extern FuncInfo<Array<uint8_t,8>> read8_info;
		extern Action1Info<Array<uint8_t,8>> write8_info;
		extern Action1Info<uint8_t> write_info;
		extern ActionInfo clear_info;
	
		/* Interface */
		class Interface
		{
			public:
			
			virtual void start(uint32_t baud, SerialPort::Config config) = 0;
			
			virtual uint16_t available() = 0;
			
			// reads a single byte from the receive buffer. if buffer is empty, 0 is returned.
			virtual uint8_t read() = 0;
			
			// reads 8 bytes from receive buffer. If there are less than 8 bytes waiting in the receive buffer then zeros are returned for the remaining bytes.
			virtual Array<uint8_t,8> read8() = 0;
			
			virtual void write(uint8_t) = 0;
			
			virtual void write8(Array<uint8_t,8>) = 0;
			
			virtual void clear() = 0;
	
			// There is no corresponding instruction for this function. It is implemented locally using other instructions.
			virtual void read(ARG_OUT uint8_t* p_dest, size_t len) = 0;
	
			// There is no corresponding instruction for this function. It is implemented locally using other instructions.
			virtual void write(uint8_t* p_source, size_t len) = 0;
		};
	
	}; //SerialShared
}

#endif //__SERIALSHARED_H__
