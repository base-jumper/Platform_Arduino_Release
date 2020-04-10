/* 
* ArrayType.h
*
* Created: 20/02/2020 9:21:50 PM
* Author: nbute
*/


#ifndef __ARRAYTYPE_H__
#define __ARRAYTYPE_H__

#include "../../Shared/Data/Array.h"
#include "ValueType.h"
#include "../../Shared/Data/OStream.h"
#include "../../Shared/Data/StringManip.h"

namespace BaseJumper
{
	template <class T, size_t num_items>
	struct ArrayType : public ValueType<Array<T,num_items>>
	{
		private:
			ValueType<T>& element_type;
	
		public:
			ArrayType(ValueType<T>& element_type_in)
			: element_type(element_type_in)
			{
			}
	
			OStream& print_range(OStream& os) const override final
			{
				os << "[";
				element_type.print_range(os);
				os << "]";
				return os;
			}
	
			bool check(Array<T,num_items> arr) const override final
			{
				bool result = true;
				for (size_t i = 0; i < num_items; i++)
				{
					result = result && element_type.check(arr[i]);
				}
				return result;
			}
	
			OStream& print(OStream& os, const Array<T,num_items> arr) const override final
			{
				os << "[";
				for (size_t i = 0; i < num_items; i++)
				{
					element_type.print(os, ((Array<T,num_items>)arr)[i]);
					if (i+1 < num_items)
						os << ", ";
				}
				os << "]";
				return os;
			}
	
			size_t parse(char* p_src, ARG_OUT bool& val_valid, ARG_OUT Array<T,num_items>& val) const override
			{
				char* p_cur = p_src;
				drop_leading_spaces(p_cur);
				if (*p_cur++ != '[')
				{
					val_valid = false;
					return 0;
				}
				for (size_t i = 0; i < num_items; i++)
				{
					drop_leading_spaces(p_cur);
					bool element_valid;
					p_cur += element_type.parse(p_cur, element_valid, val[i]);
					if (!element_valid)
					{
						val_valid = false;
						return 0;
					}
					drop_leading_spaces(p_cur);
					if (i+1 < num_items)
					{
						if (*p_cur++ != ',')
						{
							val_valid = false;
							return 0;
						}
					}
				}
				if (*p_cur++ != ']')
				{
					val_valid = false;
					return 0;
				}
				val_valid = true;
				return p_cur - p_src;
			}
	};
}

#endif //__ARRAYTYPE_H__
