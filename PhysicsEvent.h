#pragma once
#include <SmartEvent/SmartEvent.h>

namespace Collision
{
	class CollisionsThisFrame;
	class PhysicsEvent : Event::SmartEvent::SmartEvent <CollisionsThisFrame &> {};
}
