#pragma once
#include <SmartEvent/SmartEvent.h>

namespace Collision
{
	class ICollider;
}

class OverlapEvent : public Event::SmartEvent::SmartEvent<Collision::Collision, Collision::ICollider &, Collision::ICollider &>
{};