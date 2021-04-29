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
			template<class EventType>
			static EventType * requestEvent()
			{
				return SmartEventManager::getEvent<EventType>();
			}
		protected:
			template<class EventType, typename... UpdateArgs>
			static void subscribeToEvent( _ASmartObserverArgumented<UpdateArgs...> * observer )
			{
				//requestEvent<EventType>()->registerObserver( this );
				SmartEventManager::_registerObserverToEvent<EventType>( observer );
			}
			template<class EventType, typename... UpdateArgs>
			static void unsubscribeFromEvent( _ASmartObserverArgumented<UpdateArgs...> * observer )
			{
				//requestEvent<EventType>()->unregisterObserver( this );
				SmartEventManager::_unregisterObserverToEvent<EventType>( observer );
			}

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
		class ASmartObserver : EventType::UpdateArgs::template apply<_ASmartObserverArgumented>
		{
			using _updateArgsPack = typename EventType::UpdateArgs;
			using base = typename _updateArgsPack::template apply<_ASmartObserverArgumented>;
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