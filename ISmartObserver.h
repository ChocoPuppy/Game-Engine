#pragma once
#include "SmartEventManager.h"
#include "ISmartEvent.h"
namespace Event
{
	namespace SmartEvent
	{
		template<typename...>
		class ASmartEvent;

		class _ISmartObserver
		{
			template<class EventType>
			EventType * requestEvent()
			{
				return SmartEventManager::getEvent<EventType>();
			}
		protected:
			template<class EventType>
			void unsubscribeFromEvent()
			{
				requestEvent<EventType>()->registerObserver( this );
			}
			template<class EventType>
			void subscribeToEvent()
			{
				requestEvent<EventType>()->unregisterObserver( this );
			}

			virtual ~_ISmartObserver();
		};

		template<typename... _UpdateArgs>
		class _ISmartObserverArgumented : protected _ISmartObserver
		{
			using AbstractedEvent = ASmartEvent<_UpdateArgs...>;
			friend AbstractedEvent;

			virtual void update( _UpdateArgs... ) = 0;
		};

		/// @brief An observer that automatically subscribes and unsubscribes to a specific event upon creation & destruction.
		/// @tparam EventType The event type to subscribe to.
		/// @tparam ...UpdateArgs The arguments the event type will pass.
		template<class EventType>
		class ASmartObserver : EventType::UpdateArgs::template apply<_ISmartObserverArgumented>
		{
			friend class EventType::UpdateArgs::template apply<ASmartEvent>;
		public:

			ASmartObserver()
			{
				_ISmartObserver::subscribeToEvent<EventType>();
			}
			virtual ~ASmartObserver() override
			{
				_ISmartObserver::unsubscribeFromEvent<EventType>();
			}
		};
	};
}