#pragma once
#include <unordered_set>
namespace Event
{
	namespace SmartEvent
	{
		class _ISmartObserver;
		class _ISmartEvent
		{
			friend _ISmartObserver;
		protected:
			using ObserverSet = std::unordered_set<_ISmartObserver *>;
			//			virtual ObserverSet const * getObservers() const = 0;
			virtual void registerObserver( _ISmartObserver * observer ) = 0;
			virtual void unregisterObserver( _ISmartObserver * observer ) = 0;

		public:
			virtual ~_ISmartEvent() = default;
		};
	}
}
