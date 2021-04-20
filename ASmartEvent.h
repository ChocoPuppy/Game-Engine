#pragma once
#include <unordered_set>
#include <tuple>
#include "ISmartEvent.h"
#include "ISmartObserver.h"
namespace Event
{
	namespace SmartEvent
	{
		template<typename...>
		class _ISmartObserverArgumented;

		class _ASmartEvent : _ISmartEvent
		{
			friend _ISmartObserver;
			ObserverSet registeredObservers;
			virtual void registerObserver( _ISmartObserver * observer ) final;
			virtual void unregisterObserver( _ISmartObserver * observer ) final;

		protected:
			ObserverSet const * getObservers() const;
		};
		/// @brief An abstract event type. Events should have no context.
		/// @tparam ...UpdateArgs The arguments to pass when being updated. This is to pass the context of the update to the observers.
		template<typename... UpdateArgs>
		class ASmartEvent : _ASmartEvent
		{
			friend class SmartEventManager;
			friend _ISmartObserver;
		public:
			typedef updateArguments = std::tuple<UpdateArgs...>;
			void update( UpdateArgs... updateArgs )
			{
				for (_ISmartObserver * const & observer : *getObservers())
				{
					_ISmartObserverArgumented<UpdateArgs...> * argumentedObserver = dynamic_cast<_ISmartObserverArgumented<UpdateArgs...> *>( observer );
					if (argumentedObserver == nullptr)
					{
						std::cerr << "Whoops, an observer has subscribed to an event it isn't compatible with!" << std::endl;
						exit( 1 );
					}
					argumentedObserver->update( updateArgs... );
				}
			}
		};
	}
}