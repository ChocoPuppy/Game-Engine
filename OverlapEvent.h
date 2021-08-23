#pragma once
#include "CollisionTester.h"
#include <SmartEvent/SmartEvent.h>

class OverlapEvent : public Event::SmartEvent::SmartEvent<Collision::CollisionData, Collision::ICollider &, Collision::ICollider &>
{};