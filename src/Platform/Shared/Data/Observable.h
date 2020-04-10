/*
 * Observable.h
 *
 * Created: 6/04/2020 2:16:20 PM
 *  Author: nbute
 */ 


#ifndef OBSERVABLE_H_
#define OBSERVABLE_H_

#include "BaseCommon.h"
#include "../../Shared/Data/LinkedList.h"
#include "../../Shared/Data/FuncPtr.h"

namespace BaseJumper
{
	/* Types */
	typedef LinkedListIndex ObserverId;

	template <typename T>
	class IObservable
	{
		/* Member Functions */
		public:
		virtual void set(T new_val) = 0;
		virtual T get() = 0;
		// for direct read-only access to the value (where subscription is not required)
		virtual const T& direct() = 0;
		virtual ObserverId subscribe(Func2ArgPtr<T,T>& fptr) = 0;
		virtual void unsubscribe(ObserverId id) = 0;
	};

	template <typename T, uint8_t max_observers>
	class Observable : public IObservable<T>
	{
		private:
		T val;
		LinkedList<Func2ArgPtr<T,T>*,max_observers> observers;

		public:
		Observable(T val_in) : val(val_in)
		{

		}

		void set(T new_val) override
		{
			if (new_val != val)
			{
				T old_val = val;
				val = new_val;
				notify(old_val,new_val);
			}
		}

		T get() override
		{
			return val;
		}

		const T& direct()
		{
			return val;
		}

		ObserverId subscribe(Func2ArgPtr<T,T>& fptr) override final
		{
			return observers.insert(&fptr);
		}

		void unsubscribe(ObserverId id) override final
		{
			observers.remove(id);
		}

		private:
		void notify(T old_val, T new_val)
		{
			auto enumerator = observers.enumerate();
			while (enumerator.move_next())
			{
				auto& fptr = *enumerator.current();
				fptr(old_val,new_val);
			}
		}
	};
}

#endif /* OBSERVABLE_H_ */
