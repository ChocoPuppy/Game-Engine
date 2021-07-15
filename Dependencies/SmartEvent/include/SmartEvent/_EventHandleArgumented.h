#pragma once
#include "_EventHandle.h"
namespace Event
{
	namespace SmartEvent
	{
		template<typename... _UpdateArgs>
		class _EventHandleArgumented : _EventHandle
		{
		protected:
			template<typename EventType>
			void update( _UpdateArgs... arguments )
			{
				updateEvent<EventType>( arguments... );
			}
		};
	}
}
