#pragma once
#include <unordered_set>
#include <tuple>
#include <unordered_set>
#include "_ISmartEvent.h"
#include "ASmartObserver.h"
#include "ParameterPack.h"
namespace Event
{
	namespace SmartEvent
	{
		template<typename...>
		class _EventHandleArgumented;
		/// @brief All events (that want to use this smart system at least) should inherit from this. Events should be treated like they're labels/stateless.
		template<typename... _UpdateArgs>
		class SmartEvent : public _ISmartEvent
		{
			friend class SmartEventManager;

			friend _ASmartObserver;

			friend _EventHandleArgumented<_UpdateArgs...>;

			using SmartObserverWithArguments = _ASmartObserverArgumented<_UpdateArgs...>;
			std::unordered_set<SmartObserverWithArguments *> registeredObservers;

			void registerObserver( SmartObserverWithArguments * observer )
			{
				registeredObservers.insert( observer );
			}
			void unregisterObserver( SmartObserverWithArguments * observer )
			{
				registeredObservers.erase( observer );
			}

			std::unordered_set<SmartObserverWithArguments *> * getObservers()
			{
				return &registeredObservers;
			}

			void update( _UpdateArgs... updateArgs )
			{
				for (SmartObserverWithArguments * const & observer : *getObservers())
				{
					observer->update( updateArgs... );
				}
			}
		public:
			//This is public so observers can automatically use this to grab the parameters from the end event.
			using UpdateArgs = ParameterPack<_UpdateArgs...>;
		};
	}
}