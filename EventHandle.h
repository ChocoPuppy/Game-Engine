#pragma once
#include "SmartEventManager.h"
#include "ASmartEvent.h"
namespace Event
{
	namespace SmartEvent
	{
		//A non-templated EventHandle. Used to access events directly from SmartEventManager, since the SmartEventManager can't trust any templates as it doesn't know what the templates are gonna be at compile time.
		class _EventHandle
		{
		protected:
			template<class EventType>
			EventType * getEvent()
			{
				return SmartEventManager::getEvent<EventType>();
			}
		};
		template<class, typename...>
		class _EventHandle2EventHarder;

		//Gives SmartEvent a way to trust the eventHandle without knowing what classes will inherit off it.
		template<typename... UpdateArgs>
		class _EventHandleArgumented : protected _EventHandle
		{
			template<class EventType>
			SmartEvent<UpdateArgs...> * getBaseEvent()
			{
				return static_cast<SmartEvent<UpdateArgs...> *>( getEvent<EventType>() );
			}
		protected:
			template <class EventType>
			//SmartEvent can only trust this version of EventHandleArgumented to call its update, so it's gotta actually be called here. SmartEvent can't trust EventHandle since it doesn't know what subtype it's going to be a part of, so it can't name any EventHandle's as it's friend, it also can't name _EventHandle since _EventHandle doesn't actually know what arguments to call the update with. Thus this layer has gotta do it.
			void _updateEvent( UpdateArgs... args )
			{
				getBaseEvent<EventType>()->update( args... );
			}
		public:
			template <class EventType> using upgrade = _EventHandle2EventHarder<EventType, UpdateArgs...>;

			virtual void update( UpdateArgs... ) = 0;
		};

		template <class EventType, typename... UpdateArgs>
		class _EventHandle2EventHarder : protected _EventHandleArgumented<UpdateArgs...>
		{
		public:
			virtual void update( UpdateArgs... args ) override final
			{
				_EventHandleArgumented<UpdateArgs...>::template _updateEvent<EventType>( args... );
			}
		};

		/// @brief Calls an events update. Only use this for events you actually own (I can't figure out a way to ensure you can't so I'm just gonna have to trust you not to).
		/// @description Alright, so that inheritance list is a mess right? I couldn't really find any way to make it cleaner so I'll just go over what the fuck that is here: First I use the parameter pack (UpdateArgs) in EventType to produce an _EventHandleArgumented , which I used to then produce a _EventHandle2EventHarder , which is what this inherits off. Basically I had to do it that way since I needed to insert both the parameter pack (UpdateArgs) of EventType AND the EventType itself into the template parameters, but I can't pass a half-finished template into the pack, so I had to improvise. I had to do a lot of fuckery like this to make this system as quick & easy as possible (cause fuck boilerplate).
		template<class EventType>
		class EventHandle : public EventType::UpdateArgs::template apply<_EventHandleArgumented>::template upgrade<EventType>
		{};
	}
}