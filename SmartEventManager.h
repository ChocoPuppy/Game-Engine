#pragma once

#include <unordered_set>
#include <string>
#include <memory>
#include <iostream>
#include "ISmartEvent.h"
namespace Event
{
	namespace SmartEvent
	{
		class _ISmartObserver;

		class SmartEventManager
		{
			friend class _ISmartObserver;
			static std::unordered_set<std::unique_ptr<_ISmartEvent>> registeredEvents;

		public:
			template<class EventType>
			static EventType * getEvent()
			{
				for (auto & event : registeredEvents)
				{
					EventType * target = dynamic_cast<EventType *>( event.get() );
					if (target != nullptr)
					{
						return target;
					}
				}
				return nullptr;
			}
			template<class EventType>
			static EventType * registerEvent()
			{
				EventType * newObj = new EventType();
				_ISmartEvent * newEvent = static_cast<_ISmartEvent *>( newObj );
				if (newEvent == nullptr)
				{
					std::cout << "Attempted to register an invalid event type. EventType could not be cast to _ISmartEvent." << std::endl;
					return nullptr;
				}
				registeredEvents.emplace( newEvent );
				return newObj;
			}
		};
	}
}