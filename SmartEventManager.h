#pragma once

#include <unordered_set>
#include <string>
#include <memory>
#include <iostream>
#include <typeindex>
#include <unordered_map>
#include "_ISmartEvent.h"
namespace Event
{
	namespace SmartEvent
	{
		class _ASmartObserver;
		template<typename...>
		class _ASmartObserverArgumented;

		class SmartEventManager
		{
			friend class _ASmartObserver;
			friend class _EventHandle;
			//			static std::unordered_set<std::unique_ptr<_ISmartEvent>> registeredEvents;
			static std::unordered_map<std::type_index, std::unique_ptr<_ISmartEvent>> events;

			//template<class EventType>
			//static EventType * registerEvent()
			//{
			//	EventType * newObj = new EventType();
			//	_ISmartEvent * newEvent = static_cast<_ISmartEvent *>( newObj );
			//	if (newEvent == nullptr)
			//	{
			//		std::cout << "Attempted to register an invalid event type. EventType could not be cast to _ISmartEvent." << std::endl;
			//		return nullptr;
			//	}
			//	registeredEvents.emplace( newEvent );
			//	return newObj;
			//}

			//template<class EventType>
			//static EventType * getEvent()
			//{
			//	for (auto & event : registeredEvents)
			//	{
			//		EventType * target = dynamic_cast<EventType *>( event.get() );
			//		if (target != nullptr)
			//		{
			//			return target;
			//		}
			//	}
			//	return nullptr;
			//}

			template<class EventType>
			static EventType * getEvent()
			{
				std::type_index eventType = typeid( EventType );
				if (events.find( eventType ) == events.end())
				{
					std::cout << "Smart event " << eventType.name() << " referenced for first time." << std::endl;
					events.emplace( eventType, new EventType() );
				}
				return dynamic_cast<EventType *>( events.at( eventType ).get() );
			}
			/// @brief Passes registration of the observer to the event.
			/// @tparam EventType The event to register the observer to.
			/// @param observer The observer to pass
			template<class EventType, typename... UpdateArgs>
			static void _registerObserverToEvent( _ASmartObserverArgumented<UpdateArgs...> * observer )
			{
				getEvent<EventType>()->registerObserver( observer );
			}
			/// @brief Passes the unregistration of the observer to the event.
			/// @tparam EventType
			/// @param observer
			template<class EventType, typename... UpdateArgs>
			static void _unregisterObserverToEvent( _ASmartObserverArgumented<UpdateArgs...> * observer )
			{
				getEvent<EventType>()->unregisterObserver( observer );
			}
		};
	}
}