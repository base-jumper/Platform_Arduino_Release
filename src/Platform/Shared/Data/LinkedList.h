#ifndef LINKEDLINK_H_INCLUDED
#define LINKEDLINK_H_INCLUDED

#include <string.h>
#include "stdint.h"

namespace BaseJumper
{
	typedef uint16_t LinkedListIndex;
	
	template <class T, size_t list_size>
	class LinkedList 
	{
	  private:
	    T values[list_size];
	    uint16_t links[list_size];
	    LinkedListIndex first;
	    LinkedListIndex last;
	    bool is_empty;
	
	  private:
	    LinkedListIndex get_predecessor(LinkedListIndex target) const
	    {
	      // start at first populated index
	      LinkedListIndex x = first;
	      LinkedListIndex y = get_successor(x);
	      while (y != target)
	      {
	        x = y;
	        y = get_successor(y);
	      }
	      return x;
	    }
	
	    LinkedListIndex get_successor(LinkedListIndex current) const
	    {
	      return links[current];
	    }
	
	    void set_successor(LinkedListIndex index, LinkedListIndex successor_index)
	    {
	      links[index] = successor_index;
	    }
	
	  public:
	    LinkedList() 
	    {
	      first = 0;
	      last = 0;
	      is_empty = true;
	
	      // link all nodes
	      for (uint16_t i = 0; i < (list_size - 1); i++)
	        links[i] = i+1;
	      links[list_size-1] = 0;
	     }
	
	    // Precondition: !full()
	    LinkedListIndex insert(T value)
	    {
		// determine where new value will go
		auto new_index = is_empty ? last : get_successor(last);
		
		// copy value into list
	    values[new_index] = value;
		
		// update links
		last = new_index;
		
		is_empty = false;
		
		return new_index;
	    }
	
	    T& operator[] (LinkedListIndex index)
	    {
	      return values[index];
	    }
	
	    bool empty() const
	    {
	      return is_empty;
	    }
	
	    bool full() const
	    {
	      return (first == get_successor(last));
	    }
	
	    // Precondition: !empty()
	    void remove(LinkedListIndex del)
	    {
	      // delete items from list with 0 or 1 items
	      if (first == last)
	        is_empty = true;
	
	      // delete item from beginning of list
	      else if (first == del)
	        first = get_successor(del);	
	
	      // delete item from end of list
	      else if (last == del)
	        last = get_predecessor(del);
	
	      // delete item from middle of list
	      else
	      {
	        // remove node from chain
	        LinkedListIndex before_del = get_predecessor(del);
	        LinkedListIndex after_del = get_successor(del);
	        set_successor(before_del, after_del);
	
	        // insert node back into chain after last
	        LinkedListIndex after_last = get_successor(last);
	        set_successor(del, after_last);
	        set_successor(last, del);		
	      }
	    }
	
	    class Enumerator
	    {	
	      private:
	        LinkedList& list;
	        bool before_first = true;
	        LinkedListIndex current_index;
	
	      public:
	        Enumerator(LinkedList& list_in) : list(list_in)
	        {
	        }
	
	        bool move_next()
	        {
	          bool result;
	      
	          if (before_first)
	          {
	            current_index = list.first;
	            before_first = false;
	            result = !list.empty();
	          }
	          else if (current_index == list.last)
	          {
	            result = false;
	          }
	          else
	          {
	            current_index = list.get_successor(current_index);
	            result = true;
	          }
	          return result;
	        }
	
	        T& current() const
	        {
	          return list.values[current_index];
	        }
	    };
	
	    Enumerator enumerate()
	    {
	      return Enumerator(*this);
	    }
	};
}

#endif
