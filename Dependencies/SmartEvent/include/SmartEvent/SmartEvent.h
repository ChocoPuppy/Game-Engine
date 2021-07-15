#pragma once
#include "_ISmartEvent.h"
#include "ASmartObserver.h"
#include <unordered_set>
namespace Event
{
	namespace SmartEvent
	{
		template<typename...>
		class _EventHandleArgumented;

		/// @brief All events (that want to use this smart system at least) should inherit from this. Events should be treated like they're labels/stateless.
		/// @tparam _UpdateArgs The parameters that are passed along to the events observers as context.
		template<typename... _UpdateArgs>
		class SmartEvent : public _ISmartEvent
		{
			friend class SmartEventManager;

			friend _ASmartObserver;
		public:
			using _SmartObserverWithArguments = _ASmartObserverArgumented<_UpdateArgs...>;
			using _EventHandleWithArguments = _EventHandleArgumented<_UpdateArgs...>;
		private:

			std::unordered_set<_SmartObserverWithArguments *> registeredObservers;

			void registerObserver( _SmartObserverWithArguments * observer )
			{
				registeredObservers.insert( observer );
			}
			void unregisterObserver( _SmartObserverWithArguments * observer )
			{
				registeredObservers.erase( observer );
			}

			std::unordered_set<_SmartObserverWithArguments *> * getObservers()
			{
				return &registeredObservers;
			}
			void update( _UpdateArgs... updateArgs )
			{
				for (_SmartObserverWithArguments * const & observer : *getObservers())
				{
					observer->update( updateArgs... );
				}
			}
		};
	}
}