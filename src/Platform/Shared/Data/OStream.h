/* 
* OStream.h
*
* Created: 24/02/2019 9:44:16 AM
* Author: nbute
*/


#ifndef __OSTREAM_H__
#define __OSTREAM_H__
#include "../../Shared/Data/LinkedList.h"

namespace BaseJumper
{
	extern const char* endl;

	class OStream
	{
	/* functions */
	public:
		virtual OStream& operator <<(const char* val) = 0;
		virtual void start_message() {};
		virtual void end_message() {};
		virtual void put_line(char* str) 
		{
			start_message();
			*this << str << "\n\r";
			end_message();
		};
		//OStream& print(char* val);
		
		OStream& operator <<(const float val);
		OStream& operator <<(const uint8_t val);
		OStream& operator <<(const uint16_t val);
		OStream& operator <<(const uint32_t val);

		/* clashes with existing operators on arduino. */
		#ifdef BASE
		OStream& operator <<(const size_t val);
		#endif
	};
	
	/* OStreamProxy
	 * Wraps an OStream pointer. Allows OStream object to efficiently be switched
	 * behind the scenes when context changes. The consumer just interacts with an 
	 * OStream object much the same as std::cout, and doesn't have to deal with 
	 * pointers.
	 */
	class OStreamProxy : public OStream
	{
	/* member variables */	
	public:
		OStream* target;
	
	/* member functions */
	public:

		using OStream::operator<<;

		OStream& operator <<(const char* val) override final
		{
			if (target)
				return (*target) << val;
			return *this;
		}
	
		void start_message() override final
		{
			if (target)
				(*target).start_message();
		}
	
		void end_message() override final
		{
			if (target)
				(*target).end_message();
		}
	};
	
	/* CompoundOStream
	 * Maps a single stream to multiple streams.
	 */
	class CompoundOStream : public OStream
	{
	/* Types */
	private:
		struct Entry
		{
			const char* prefix;
			OStream* p_ostream;
		};	
	public:
		typedef LinkedListIndex StreamId;
	
	/* Static variables */
	public:
		static constexpr size_t max_streams = 5;
	
	/* Member variables */
	private:
		LinkedList<Entry,max_streams> streams;
	
	/* Member functions */
	public:
		StreamId add(const char* prefix, OStream& stream)
		{
			Entry entry { prefix, &stream };
			return streams.insert(entry);
		}
	
		StreamId add(OStream& stream)
		{
			return add("", stream);
		}
	
		void remove(StreamId id)
		{
			streams.remove(id);
		}
	
		using OStream::operator<<;

		OStream& operator <<(const char* val) override final
		{
			auto enumerator = streams.enumerate();
			while (enumerator.move_next())
			{
				auto entry = enumerator.current();
				OStream& os = *entry.p_ostream;
				os << val;
			}
			return *this;
		}
	
		void start_message() override final
		{
			auto enumerator = streams.enumerate();
			while (enumerator.move_next())
			{
				auto entry = enumerator.current();
				auto prefix = entry.prefix;
				OStream& os = *entry.p_ostream;
				if (strlen(prefix) > 0)
					os << "[" << prefix << "] ";
			}
		}
	
	};
	
	class StringStream : public OStream
	{
	private:
		char* str;
		const size_t len;
		size_t index = 0;
	
	public:
		StringStream(char* str_in, size_t len_in) 
		: str(str_in), len(len_in)
		{
		}
	
		using OStream::operator<<;

		virtual OStream& operator <<(const char* val) override final
		{
			const char* p = val;
			while (*p)
			{
				str[index++] = *p;
				p++;
			}
			str[index] = '\0';
			return *this;
		}
	};
	
	class NullStream : public OStream
	{
		OStream& operator <<(const char* val) override final
		{
			// do nothing.
			return *this;
		}
	};
	
	template <uint8_t num_cols>
	class TableStream : public OStream
	{
		private:
		OStream& os;
		bool first_row = true;
		uint8_t col_index = 0;
		uint8_t col_widths[num_cols];

		public:
		TableStream(OStream& os_in) : os(os_in)
		{

		}

		using OStream::operator<<;

		OStream& operator <<(const char* val) override final
		{
			auto len = strlen(val);
			bool end_of_row = (col_index + 1 == num_cols);
			if (first_row)
			{
				col_widths[col_index] = len;
				os << val;
				if (!end_of_row)
					os << " | ";
				first_row = !end_of_row;
			}
			else
			{
				os << val;
				while (len++ < col_widths[col_index])
					os << " ";
				if (!end_of_row)
					os << " | ";
			}
			if (end_of_row)
			{
				os << endl;
				col_index = 0;
			}
			else
			{
				col_index++;
			}
			return *this;
		}
	};

	extern NullStream null_stream;

}

#endif //__OSTREAM_H__
