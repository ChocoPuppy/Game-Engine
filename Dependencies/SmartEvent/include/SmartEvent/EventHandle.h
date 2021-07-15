#pragma once
#include "_EventHandleArgumented.h"
namespace Event
{
	namespace SmartEvent
	{
		template<typename EventType>
		class EventHandle : EventType::_EventHandleWithArguments
		{
			using Base = typename EventType::_EventHandleWithArguments;
		public:
			template<typename... _UpdateArgs>
			auto update( _UpdateArgs... arguments )
			{
				return Base::update<EventType>( arguments... );
			}
		};

		/*
		template<class, typename, typename...>
		class _EventHandle2EventHarder;

		//Gives SmartEvent a way to trust the eventHandle without knowing what classes will inherit off it.
		template<typename _Return, typename... UpdateArgs>
		class _EventHandleArgumented : protected _EventHandle
		{
			template<class EventType>
			SmartEvent<_Return, UpdateArgs...> * getBaseEvent()
			{
				return static_cast<SmartEvent<ReturnAndUpdateArgs...> *>( getEvent<EventType>() );
			}
		protected:
			template <class EventType>
			//SmartEvent can only trust this version of EventHandleArgumented to call its update, so it's gotta actually be called here. SmartEvent can't trust EventHandle since it doesn't know what subtype it's going to be a part of, so it can't name any EventHandle's as it's friend, it also can't name _EventHandle since _EventHandle doesn't actually know what arguments to call the update with. Thus this layer has gotta do it.
			std::unordered_set<_Return> _updateEvent( UpdateArgs... args )
			{
				return getBaseEvent<EventType>()->update( args... );
			}
		public:
			//Construct the template parameters of _EventHandle2EventHarder using the passed event type and the known return and update arguments.
			template <class EventType> using upgrade = _EventHandle2EventHarder<EventType, _Return, UpdateArgs...>;
		};

		//A version of the event handle that knows both the return + update args and the actual class type it's looking for.
		template <class EventType, typename _Return, typename... UpdateArgs>
		class _EventHandle2EventHarder : protected _EventHandleArgumented<_Return, UpdateArgs...>
		{
		public:
			std::unordered_set<_ReturnType> update( ReturnAndUpdateArgs... args )
			{
				_updateEvent<EventType>( args... );
			}
		};
		//A partial template specialization for _EventHandle2EventHarder that doesn't attempt to get a set of return values since the return type is void.
		template<class EventType, typename... UpdateArgs>
		class _EventHandle2EventHarder<EventType, void, UpdateArgs...> : protected _EventHandleArgumented<void, UpdateArgs...>
		{
		public:
			void update( UpdateArgs... args )
			{
				_updateEvent<EventType>( args... );
			}
		}
				/// @brief Calls an events update. You should pretty much only use this for events you actually own (I can't figure out a way to ensure this so I'm just gonna have to trust you not to).
		template<class EventType>
		using EventHandle = EventType::ReturnAndUpdateArgs::template apply<_EventHandleArgumented>::template upgrade<EventType>;

		;*/

		/// @description Alright, so that inheritance list is a mess right? I couldn't really find any way to make it cleaner so I'll just go over what exactly is going on there: First I use the parameter pack (UpdateArgs) in EventType to produce an _EventHandleArgumented , which I used to then produce a _EventHandle2EventHarder , which is what this inherits off. Basically I had to do it that way since I needed to insert both the parameter pack (UpdateArgs) of EventType AND the EventType itself into the template parameters, but I can't pass a half-finished template into the pack, so I had to improvise. I had to do a lot of fuckery like this to make this system as quick & easy as possible (cause fuck boilerplate).
/*		template<class EventType>
		class EventHandle : public EventType::ReturnAndUpdateArgs::template apply<_EventHandleArgumented>::template upgrade<EventType>
		{};*/
	}
}