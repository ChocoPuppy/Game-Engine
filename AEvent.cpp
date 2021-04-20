#include "AEvent.h"

void Event::AEvent::update(std::string* message)
{
	for (IObserver* observer : observers) 
	{
		observer->update(message);
	}
}

void Event::AEvent::addObserver(IObserver* observer)
{
	observers.insert(observer);
}

void Event::AEvent::removeObserver(IObserver* observer)
{
	observers.erase(observer);
}
