#pragma once
#include <SmartEvent/SmartEvent.h>

namespace
{
	class CollisionsThisFrame;
	class OverlapEvent : public Event::SmartEvent::SmartEvent<CollisionsThisFrame &> {};
}
