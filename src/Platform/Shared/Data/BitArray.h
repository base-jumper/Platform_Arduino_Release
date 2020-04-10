/*
 * BitArray.h
 *
 * Created: 13/03/2020 9:18:08 PM
 *  Author: nbute
 */ 


#ifndef BITARRAY_H_
#define BITARRAY_H_

#include "BitByte.h"

namespace BaseJumper
{
	template <size_t bitlen>
	class BitArray
	{
		public:
		static constexpr size_t encoded_len = bitlen / 8 + 1;

		public:
		static inline size_t byte_index(size_t index)
		{
			return index / 8;
		}

		static inline uint8_t bit_index(size_t index)
		{
			return index % 8;
		}

		private:
		BitByte data[bitlen/8 + 1];

		public:
		BitArray()
		{
		}

		BitArray(uint8_t* p_encoded)
		{
			memcpy(data, p_encoded, encoded_len);
		}

		bool get(size_t index) 
		{
			auto byte = byte_index(index);
			auto bit = bit_index(index);
			return data[byte].get(bit);
		}

		void set(size_t index, bool val)
		{
			auto byte = byte_index(index);
			auto bit = bit_index(index);
			data[byte].set(bit, val);
		}

		void set_all(bool val)
		{
			memset(data, val ? 0xff : 0x00, bitlen/8+1);
		}

		void encode(ARG_OUT uint8_t* p_dst)
		{
			memcpy(p_dst, data, encoded_len);
		}
	};
}


#endif /* BITARRAY_H_ */
