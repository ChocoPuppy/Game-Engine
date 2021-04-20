#include "ASmartEvent.h"
using namespace Event::SmartEvent;
void _ASmartEvent::registerObserver( _ISmartObserver * observer )
{
	registeredObservers.insert( observer );
}

void _ASmartEvent::unregisterObserver( _ISmartObserver * observer )
{
	registeredObservers.erase( observer );
}

_ASmartEvent::ObserverSet const * _ASmartEvent::getObservers() const
{
	return &registeredObservers;
}