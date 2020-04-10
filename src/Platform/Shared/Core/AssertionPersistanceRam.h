/*
 * AssertionPersistance.h
 *
 * Created: 16/03/2020 8:51:37 AM
 *  Author: nbute
 */ 


#ifndef ASSERTIONPERSISTANCERAM_H_
#define ASSERTIONPERSISTANCERAM_H_

#include "AssertionManager.h"

namespace BaseJumper
{
	template <size_t _max_assertions>
	class AssertionPersistanceRam : public IAssertionManager::IPersistance<_max_assertions>
	{
		BitArray<_max_assertions> faileds;

		public:
		AssertionPersistanceRam()
		{
		}

		BitArray<_max_assertions> sync_faileds() override final
		{
			return faileds;
		}

		bool get_failed(size_t index) override final
		{
			return faileds.get(index);
		}

		void set_failed(size_t index, bool val) override final
		{
			faileds.set(index, val);
		}

		void clear() override final
		{
			faileds.set_all(false);
		}
	};
}


#endif /* ASSERTIONPERSISTANCERAM_H_ */
