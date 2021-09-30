#pragma once
#include <SmartEvent/SmartEvent.h>

namespace Collision
{
	struct CollisionsThisFrame;
	class OverlapEvent : public Event::SmartEvent::SmartEvent<CollisionsThisFrame *> {};
}
