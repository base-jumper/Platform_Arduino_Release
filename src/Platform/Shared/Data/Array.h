/* 
* Array.h
*
* Created: 20/02/2020 9:13:57 PM
* Author: nbute
*/


#ifndef __ARRAY_H__
#define __ARRAY_H__

namespace BaseJumper
{
	template <class T, size_t num_items>
	struct Array
	{
		/* Member Variables */
		T items[num_items];
	
		/* Member Functions */
		Array()
		{
		}
		
		Array(T* p_items)
		{
			memcpy(items, p_items, num_items);
		}
	
	    T& operator[] (size_t index)
	    {
		    return items[index];
	    }
	
		size_t size()
		{
			return num_items;
		}
	};
}

#endif //__ARRAY_H__
