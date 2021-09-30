#pragma once
#include <tuple>
#include "ParameterPack.h"
namespace Collision
{
	class RectCollider2D;
	class CircleCollider2D;
	using ColliderTypes = ParameterPack<RectCollider2D, CircleCollider2D>;
}