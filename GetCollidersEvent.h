#pragma once
#include <vector>
#include <SmartEvent/SmartEvent.h>

namespace Collision
{
	class ICollider;
	//This is hacky as shit but I can't figure out much of a better way to ensure the colliders are known by the physicsEngine without the colliders needing a reference back to the physicsEngine at creation. I'll have to figure a better arrangement out later :M
	class GetCollidersEvent : public Event::SmartEvent::SmartEvent<std::vector<ICollider *> *> {};
}