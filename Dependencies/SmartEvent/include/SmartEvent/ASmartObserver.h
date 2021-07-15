#pragma once
#include "SmartEventManager.h"
#include "_ISmartEvent.h"
#include <iostream>
namespace Event
{
	namespace SmartEvent
	{
		template<typename...>
		class SmartEvent;

		class _ASmartObserver
		{
		protected:
			template<class EventType, typename... _UpdateArgs>
			static void subscribeToEvent( _ASmartObserverArgumented<_UpdateArgs...> * observer )
			{
				SmartEventManager::_registerObserverToEvent<EventType>( observer );
			}
			template<class EventType, typename... _UpdateArgs>
			static void unsubscribeFromEvent( _ASmartObserverArgumented<_UpdateArgs...> * observer )
			{
				SmartEventManager::_unregisterObserverToEvent<EventType>( observer );
			}
		public:
			virtual ~_ASmartObserver() = default;
		};

		template<typename... _UpdateArgs>
		class _ASmartObserverArgumented : protected _ASmartObserver
		{
			using AbstractedEvent = SmartEvent<_UpdateArgs...>;
			friend AbstractedEvent;

			virtual void update( _UpdateArgs... ) = 0;
		};

		/// @brief An observer that automatically subscribes and unsubscribes to a specific event upon creation & destruction.
		/// @tparam EventType The event type to subscribe to.
		/// @tparam ...UpdateArgs The arguments the event type will pass.
		template<class EventType>
		class ASmartObserver : EventType::_SmartObserverWithArguments
		{
			using base = typename EventType::_SmartObserverWithArguments;
			friend base;

		public:

			ASmartObserver()
			{
				_ASmartObserver::subscribeToEvent<EventType>( static_cast<base *>( this ) );
				std::cout << "Event has been subscribed." << std::endl;
			}
			virtual ~ASmartObserver() override
			{
				_ASmartObserver::unsubscribeFromEvent<EventType>( static_cast<base *>( this ) );
				std::cout << "Event has been unsubscribed." << std::endl;
			}
		};
	};
}