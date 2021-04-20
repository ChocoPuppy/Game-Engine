#pragma once
#include "SmartEventManager.h"
#include "ISmartEvent.h"
#include <stdexcept>
#include <tuple>
namespace Event
{
	namespace SmartEvent
	{
		template<typename...>
		class ASmartEvent;

		class _ISmartObserver
		{
			template<class EventType>
			static EventType * requestEvent()
			{
				return SmartEventManager::getEvent<EventType>();
			}
			template<class EventType>
			static _ISmartEvent * requestGenericEvent()
			{
				EventType * baseEvent = requestEvent<EventType>();
				_ISmartEvent * genericEvent = static_cast<_ISmartEvent *>( baseEvent );
				if (genericEvent == nullptr)
				{
					throw new std::invalid_argument( "The event type cannot be converted to ASmartEvent." );
					exit( 1 );
				}
				return genericEvent;
			}
		protected:
			template<class EventType>
			void unsubscribeFromEvent()
			{
				requestGenericEvent<EventType>()->unregisterObserver( this );
			}
			template<class EventType>
			void subscribeToEvent()
			{
				requestGenericEvent<EventType>()->registerObserver( this );
			}

			virtual ~_ISmartObserver();
		};

		template<typename... UpdateArgs>
		class _ISmartObserverArgumented : protected _ISmartObserver
		{
			friend ASmartEvent<UpdateArgs...>;

			virtual void update( UpdateArgs... ) = 0;
		};

		/// @brief An observer that automatically subscribes and unsubscribes to a specific event upon creation & destruction.
		/// @tparam EventType The event type to subscribe to.
		/// @tparam ...UpdateArgs The arguments the event type will pass.
		template<class EventType, typename... UpdateArgs>
		class ASmartObserver : _ISmartObserverArgumented<UpdateArgs...>
		{
			friend class ASmartEvent<UpdateArgs...>;

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