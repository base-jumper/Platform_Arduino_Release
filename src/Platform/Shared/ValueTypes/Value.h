/*
 * Value.h
 *
 * A convenience class for reading/writing a value to a stream.
 * Example: cout << EncodedValue(type, p_data);
 * Rather than: type.print_encoded(cout, p_data);
 */ 

#ifndef VALUE_H_
#define VALUE_H_

namespace BaseJumper
{
	struct EncodedValue
	{
		const IValueType& type;
		const uint8_t* p_data;
	
		EncodedValue(const IValueType& type_in, const uint8_t* p_data_in) 
		: type(type_in), p_data(p_data_in)
		{}
	
		friend OStream& operator<<(OStream& os, const EncodedValue& val)
		{
			return val.type.print_encoded(os, val.p_data);
		}
	};
	
	template <class T>
	struct Value
	{
		const ValueType<T>& type;
		const T& data;
	
		Value(const ValueType<T>& type_in, const T& data_in)
		: type(type_in), data(data_in)
		{
		}
	
		friend OStream& operator<<(OStream& os, const Value& val)
		{
			return val.type.print(os, val.data);
		}
	};
}

#endif /* VALUE_H_ */
