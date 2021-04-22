#pragma once
#include <unordered_set>
#include <tuple>
#include <unordered_set>
#include "ISmartEvent.h"
#include "ISmartObserver.h"
#include "ParameterPack.h"
namespace Event
{
	namespace SmartEvent
	{
		/// @brief An abstract event type. Events should have no context.
		template<typename... _UpdateArgs>
		class ASmartEvent : public _ISmartEvent
		{
			friend class SmartEventManager;
			friend _ISmartObserver;

			using SmartObserverWithArguments = _ISmartObserverArgumented<_UpdateArgs...>;
			std::unordered_set<SmartObserverWithArguments *> registeredObservers;

			void registerObserver( _ISmartObserver * observer )
			{
				registeredObservers.insert( dynamic_cast<SmartObserverWithArguments *>( observer ) );
			}
			void unregisterObserver( _ISmartObserver * observer )
			{
				registeredObservers.erase( dynamic_cast<SmartObserverWithArguments *>( observer ) );
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
			using UpdateArgs = ParameterPack<_UpdateArgs...>;
		};
	}
}