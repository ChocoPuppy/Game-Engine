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
		template<typename...>
		class _ASmartObserverArgumented;
		template<typename...>
		class SmartEvent;

		class SmartEventManager
		{
			friend class _ASmartObserver;
			friend class _EventHandle;
			//			static std::unordered_set<std::unique_ptr<_ISmartEvent>> registeredEvents;

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
			static EventType * _getEvent()
			{
				static std::unordered_map<std::type_index, std::unique_ptr<_ISmartEvent>> events;// = std::unordered_map<std::type_index, std::unique_ptr<_ISmartEvent>>()
				std::type_index const eventType = typeid( EventType );
				if (events.find( eventType ) == events.end())
				{
					std::cout << "Smart event " << eventType.name() << " referenced for first time." << std::endl;
					events.emplace( eventType, std::make_unique<EventType>() );
				}
				return dynamic_cast<EventType *>( events.at( eventType ).get() );
			}

			template<class EventType, typename... _UpdateArgs>
			static SmartEvent< _UpdateArgs...> * _getGenericEvent()
			{
				return static_cast<SmartEvent<_UpdateArgs...> *>( _getEvent<EventType>() );
			}

			template<class EventType, typename... _UpdateArgs>
			static void _updateEvent( _UpdateArgs... parameters )
			{
				return _getGenericEvent<EventType, _UpdateArgs...>()->update( parameters... );
			}

			/// @brief Passes registration of the observer to the event.
			/// @tparam EventType The event to register the observer to.
			/// @param observer The observer to pass.
			template<class EventType, typename... _UpdateArgs>
			static void _registerObserverToEvent( _ASmartObserverArgumented<_UpdateArgs...> * observer )
			{
				_getEvent<EventType>()->registerObserver( observer );
			}
			/// @brief Passes the unregistration of the observer to the event.
			/// @tparam EventType
			/// @param observer
			template<class EventType, typename... _UpdateArgs>
			static void _unregisterObserverToEvent( _ASmartObserverArgumented<_UpdateArgs...> * observer )
			{
				_getEvent<EventType>()->unregisterObserver( observer );
			}
		};
	}
}