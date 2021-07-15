#pragma once
#include "SmartEventManager.h"
namespace Event
{
	namespace SmartEvent
	{
		//A non-templated EventHandle. Used to access events directly from SmartEventManager, since the SmartEventManager can't trust any templates as it doesn't know what the templates are gonna be at compile time.
		class _EventHandle
		{
		protected:
			template<class EventType, typename... _UpdateArgs>
			void updateEvent( _UpdateArgs... arguments )
			{
				return SmartEventManager::_updateEvent<EventType, _UpdateArgs...>( arguments... );
			}
		};
	}
}
