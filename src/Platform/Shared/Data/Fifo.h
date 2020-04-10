#if 1
#ifndef DATA_FIFO_H_
#define DATA_FIFO_H_

#include <stddef.h>

namespace BaseJumper
{
	template <class T, size_t num_items> class Fifo {
	  private:
	  T buffer[num_items+1];
	  size_t head;	// points to the location where the next item should be added
	  size_t tail;	// points to the location where the first item is currently stored
	
	  public:
	  Fifo() : head(0), tail(0)
	  {
	  }
	
	  bool full()
	  {
	    return (((head + 1) % (num_items + 1)) == tail);
	  }
	
	  bool empty()
	  {
	    return (head == tail);
	  }
	
	  // Requirement: !fifo_full(p_fifo)
	  void put(T item)
	  {
	    buffer[head] = item;
	    head = (head + 1) % (num_items + 1);
	  }
	
	  void put(const T* items, size_t item_count)
	  {
	    for (size_t i = 0; i < item_count; i++)
	      put(items[i]);
	  }
	
	  // Requirement: !fifo_empty(p_fifo)
	  T peek()
	  {
	    return buffer[tail];
	  }
	
	  // Requirement: !fifo_empty(p_fifo)
	  T get()
	  {
	    T result = peek();
	    skip();
	    return result;
	  }
	
	  void get(T* dest, size_t item_count)
	  {
	    for (size_t i = 0; i < item_count; i++)
	      dest[i] = get();
	  }
	
	  // Requirement: !fifo_empty(p_fifo)
	  void skip()
	  {
	    tail = (tail + 1) % (num_items + 1);
	  }
	
	  void clear()
	  {
	    head = tail = 0;
	  }
	
	  size_t count()
	  {
	    return head >= tail ? head - tail : num_items + 1 - tail + head;
	  }
	
	  size_t count_remaining()
	  {
		return num_items - count();
	  }
	};
}

#endif /* DATA_FIFO_H_ */
#endif
