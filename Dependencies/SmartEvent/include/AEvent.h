#pragma once
#include <string>
#include <unordered_set>

#include "IObserver.h"
namespace Event
{
	class AEvent
	{
		std::unordered_set<IObserver *> observers;
	protected:
		inline void update( std::string * message )
		{
			for (IObserver * observer : observers)
			{
				observer->update( message );
			}
		}
	public:
		inline void addObserver( IObserver * observer )
		{
			observers.insert( observer );
		}
		inline void removeObserver( IObserver * observer )
		{
			observers.erase( observer );
		}
	};
}
