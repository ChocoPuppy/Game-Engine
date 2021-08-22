#pragma once
#include "Vector2D.h"
#include "ICollider.h"
#include "RectCollider2D.h"
#include <type_traits>
namespace Collision
{
	struct Collision
	{
		float intersectDistance;
	};
	/// @brief A std::hash-like class for specialized overlap checking functions. This default implementation prevents test from being called since it's not a specialization.
	/// @tparam ColliderA
	/// @tparam ColliderB
	template<class ColliderA, class ColliderB>
	class TestForSpecificOverlap
	{
		TestForSpecificOverlap() = delete;
		TestForSpecificOverlap( TestForSpecificOverlap const & ) = delete;
		TestForSpecificOverlap( TestForSpecificOverlap && ) = delete;
		void operator=( TestForSpecificOverlap const & ) = delete;
		void operator=( TestForSpecificOverlap && ) = delete;

		Collision test( ColliderA const & colliderA, ColliderB const & colliderB ) = delete;
	};

	template<class ColA, class ColB>
	Collision testSpecificOverlap( ColA const & colA, ColB const & colB )
	{
		Collision result = Collision();
		//Check if a specified overlap test exists of either order. If it does, replace the result with that.
		if (std::is_default_constructible_v<TestForSpecificOverlap<ColA, ColB>>)
		{
			result = TestForSpecificOverlap<ColA, ColB>().test( colA, colB );
		}
		else if (std::is_default_constructible_v<TestForSpecificOverlap<ColB, ColA>>)
		{
			result = TestForSpecificOverlap<ColB, ColA>().test( colB, colA );
		}
		return result;
	}

	Collision testForGenericOverlap( ICollider const & colA, ICollider const & colB );

	Vector2D relativeColliderPositionToWorldPosition( Vector2D relativePosition, Vector2D worldPosition );

	//	Collision rectOverlap( ColliderAtPosition const & colA, ColliderAtPosition const & colB );

	/// @brief Tests if two colliders are overlapping. If the bounding boxes of the colliders aren't overlapping, the specific overlap tests aren't run.
	/// @tparam ColA
	/// @tparam ColB
	/// @param colA
	/// @param colB
	/// @return Data about the overlap (or lack thereof).
	template<class ColA, class ColB>
	Collision testForOverlap( ColA const & colA, ColB const & colB )
	{
		Collision result = testForGenericOverlap( colA, colB );
		if (result.intersectDistance != 0)
		{
			Collision specificResult = testSpecificOverlap<ColA, ColB>( colA, colB );
			if (specificResult.intersectDistance != 0)
			{
				result = specificResult;
			}
		}
		return result;
	}
}