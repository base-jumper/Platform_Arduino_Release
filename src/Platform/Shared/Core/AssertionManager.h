/*
 * AssertionManager.h
 *
 * Created: 16/03/2020 10:05:36 AM
 *  Author: nbute
 */ 


#ifndef ASSERTIONMANAGER_H_
#define ASSERTIONMANAGER_H_

#include "../../Shared/SharedCommon.h"
#include "Assertion.h"
#include "../../Shared/Data/OStream.h"
#include "../../Shared/Data/BitArray.h"

namespace BaseJumper
{
	enum ClassId : uint8_t;

	class IAssertionManager
	{
		/* Types */
		public:
		class AssertionBuilder
		{
			/* Member Variables */
			private:
			IAssertionManager& manager;
			const ClassId class_id;
			const uint8_t instance_id;
			uint8_t next_local_id = 0;

			/* Member Functions */
			public:
			AssertionBuilder(IAssertionManager& manager_in, ClassId class_id_in, uint8_t instance_id_in)
			: manager(manager_in), class_id(class_id_in), instance_id(instance_id_in)
			{
			}

			Assertion* create()
			{
				return manager.create(class_id, instance_id, next_local_id++);
			}
		};

		template <size_t _max_assertions>
		class IPersistance
		{
			public:
			virtual BitArray<_max_assertions> sync_faileds() = 0;
			virtual bool get_failed(size_t index) = 0;
			virtual void set_failed(size_t index, bool val) = 0;
			virtual void clear() = 0;
		};

		/* Member Functions */
		public:
		virtual void set_fault_handler(Func1ArgPtr<Assertion&>& handler_fptr) = 0;
		virtual void init() = 0;
		virtual Assertion* create(ClassId class_id, uint8_t instance_id, uint8_t local_id) = 0;
		virtual void update() = 0;
		virtual void clear_faults() = 0;
		virtual void print_faults() = 0;
		virtual AssertionBuilder create_builder(ClassId class_id) = 0;
	};
	
	// concrete class used to construct an IAssertionManager with appropriate storage space
	template <size_t _num_classes, size_t _max_assertions>
	class AssertionManager : public IAssertionManager
	{
		/* Member Variables */
		private:
		uint8_t obj_instances[_num_classes]; 
		Assertion entries[_max_assertions]; 
		IPersistance<_max_assertions>& persistance;   // for persistant storage of failures ('ever' flag)
		size_t next_index = 0;		// increments each time an assertion is created
		Func1ArgPtr<Assertion&>* p_handler_fptr; // function to receive callback when an assertion fails

		/* Member Functions */
		public:
		AssertionManager(IPersistance<_max_assertions>& persistance_in) 
		: persistance(persistance_in)
		{}

		void init() override final
		{
			auto faileds = persistance.sync_faileds();
			for (size_t i = 0; i < _max_assertions; i++)
			{
				entries[i].failed_ever = faileds.get(i);
			}
		}

		void set_fault_handler(Func1ArgPtr<Assertion&>& handler_fptr) override final
		{
			p_handler_fptr = &handler_fptr;
		}

		void update() override final
		{
			// update persistence
			for (size_t i = 0; i < next_index; i++)
			{
				auto& assertion = entries[i];
				if (assertion.failed_ever_changed)
				{
					assertion.failed_ever_changed = false;
					bool failed_ever = assertion.failed_ever;
					persistance.set_failed(i, failed_ever);
				}
			}

			// update callbacks
			for (size_t i = 0; i < next_index; i++)
			{
				auto& assertion = entries[i];
				if (assertion.failed_now_changed)
				{
					assertion.failed_now_changed = false;
					if (p_handler_fptr != nullptr)
						(*p_handler_fptr)(assertion);
				}
			}
		}

		void clear_faults() override final
		{
			// clear flags on the assertion object
			for (size_t i = 0; i < next_index; i++)
			{
				auto& assertion = entries[i];
				assertion.failed_now = false;
				assertion.failed_ever = false;
				assertion.failed_ever_changed = false;
				assertion.failed_now_changed = false;
			}
		
			// clear persistent 'ever' flag
			persistance.clear();
		}

		void print_faults() override final
		{
			cout.start_message();
			TableStream<6> table(cout);
			table << "Index" << "Class Id" << "Instance Id" << "Assertion Id" << "Failed Now" << "Failed Ever";
			for (size_t i = 0; i < next_index; i++)
			{
				auto& assertion = entries[i];
				table
				<< static_cast<uint16_t>(i)
				<< assertion.class_id
				<< assertion.instance_id
				<< assertion.local_id
				<< (assertion.failed_now ? "yes" : "no")
				<< (assertion.failed_ever ? "yes" : "no");
			}
			cout.end_message();
		}

		Assertion* create(ClassId class_id, uint8_t instance_id, uint8_t local_id) override final
		{
			Assertion& assertion = entries[next_index];
			assertion.class_id = class_id;
			assertion.instance_id = instance_id;
			assertion.local_id = local_id;
			next_index++;
			return &assertion;		
		}

		IAssertionManager::AssertionBuilder create_builder(ClassId class_id) override final
		{
			
			return IAssertionManager::AssertionBuilder(*this, class_id, obj_instances[class_id]++);
		}
	};

	/* External Dependencies */
	// Each board creates its own store. This allows the size to be tailored depending on how much is needed for that particular board.
	extern IAssertionManager& assertion_manager;
}

#endif /* ASSERTIONMANAGER_H_ */
