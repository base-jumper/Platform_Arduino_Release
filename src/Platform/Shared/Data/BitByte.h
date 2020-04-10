/*
 * BitByte.h
 *
 * Created: 14/03/2020 9:37:16 AM
 *  Author: nbute
 */ 


#ifndef BITBYTE_H_
#define BITBYTE_H_


namespace BaseJumper
{

	struct BitByte
	{
		uint8_t byte;

		BitByte() : byte(0x00)
		{
		}

		BitByte(uint8_t val) : byte(val)
		{
		}

		inline bool get(uint8_t index)
		{
			return (((byte >> index) & 0x01) > 0);
		}

		inline void set(uint8_t index, bool val)
		{
			uint8_t v = val ? 1 : 0;
			byte = (byte & ~(1 << index)) | (v << index);
		}
	};

}


#endif /* BITBYTE_H_ */
