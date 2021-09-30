#pragma once
#include <SmartEvent/SmartEvent.h>

namespace Collision
{
	struct CollisionsThisFrame;
	class PhysicsEvent : public Event::SmartEvent::SmartEvent <CollisionsThisFrame *> {};
}
