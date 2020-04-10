/*
 * Broker.h
 *
 * Created: 15/01/2019 9:16:14 PM
 *  Author: nbute
 */ 

#ifndef BROKER_H_
#define BROKER_H_

#include <stdint.h>
#include <stdbool.h>

namespace BaseJumper
{
	typedef uint8_t BrokerIndex;
	
	template<typename T, size_t broker_size> class Broker
	{
	private:
		T* assets;
		uint8_t links[broker_size];
	
		uint8_t first_unused;
	
	private:
		void init_indexes()
		{
			for (uint8_t i = 0; i < broker_size; i++)
				links[i] = i;
		}
	
	public:
		Broker(T* assets_in) : assets(assets_in)
		{
			first_unused = 0;
			init_indexes();
		}
	
		// Precondition: !full()
		inline BrokerIndex allocate()
		{
			BrokerIndex index = links[first_unused];
			first_unused++;
			return index;
		}
	
		// Precondition: !empty()
		void deallocate(BrokerIndex index)
		{
			uint8_t* p_dealloc_index = links;
			while (*p_dealloc_index != index)
				p_dealloc_index++;
		
			uint8_t* p_last_allocated_index = links + first_unused - 1;
	
			uint8_t last_allocated_index = *p_last_allocated_index;
			*p_last_allocated_index = *p_dealloc_index;
			*p_dealloc_index = last_allocated_index;
		
			first_unused--;
		}
	
	    T& operator[] (BrokerIndex index)
	    {
		    return assets[index];
	    }
	
		inline size_t remaining()
		{
			return broker_size - first_unused;
		}

		inline bool full()
		{
			return first_unused >= broker_size;
		}
	
		inline bool empty()
		{
			return first_unused == 0;
		}
	
		friend class Enumerator;
	
		class Enumerator
		{
		private:
			Broker& broker;
			bool before_first;
			size_t link_index;
		public:
			BrokerIndex index;
				
			Enumerator(Broker& broker_in) : broker(broker_in), before_first(true)
			{
			}
	
		public:
			bool move_next()
			{
				bool result;
		
				if (before_first)
				{
					link_index = 0;
					index = broker.links[link_index];
					before_first = false;
					result = !broker.empty();
				}
				else if (link_index + 1 >= broker.first_unused)
				{
					result = false;
				}
				else
				{
					link_index++;
					index = broker.links[link_index];
					result = true;
				}
				return result;
			}
	
			T& current()
			{
				return broker[index];
			}
	
			friend class Broker;
		};
	
		Enumerator enumerate()
		{
			return Enumerator(*this);
		}
	
	};
}

#endif /* BROKER_H_ */
