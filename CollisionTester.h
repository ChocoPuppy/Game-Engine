#pragma once
#include "Vector2D.h"
#include "ICollider.h"
#include "RectCollider2D.h"
#include <type_traits>
namespace Collision
{
	struct CollisionData
	{
		float intersectDistance;
	};

	/// @brief A std::hash-like class for specialized overlap checking functions. This default implementation can't be called.
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

		CollisionData test( ColliderA const & colliderA, ColliderB const & colliderB ) = delete;
	};

	namespace
	{
		template<class ColA, class ColB>
		using DoesSpecificOverlapTestForPairExist = std::is_default_constructible<TestForSpecificOverlap<ColA, ColB>>;
	}
	//If there's no overload for TestForSpecificOverlap then just return blank data.
	template<class ColA, class ColB>
	typename std::enable_if_t<( !DoesSpecificOverlapTestForPairExist<ColA, ColB>::value && !DoesSpecificOverlapTestForPairExist<ColB, ColA>::value ), CollisionData>
		testSpecificOverlap( ColA const & colA, ColB const & colB )
	{
		return CollisionData{};
	}
	//Otherwise run the overlap test and return that.
	template<class ColA, class ColB>
	typename std::enable_if_t<DoesSpecificOverlapTestForPairExist<ColA, ColB>::value, CollisionData>
		testSpecificOverlap( ColA const & colA, ColB const & colB )
	{
		return TestForSpecificOverlap<ColA, ColB>.test( colA, colB );
	}

	template<class ColA, class ColB>
	typename std::enable_if_t<DoesSpecificOverlapTestForPairExist<ColB, ColA>::value, CollisionData>
		testSpecificOverlap( ColA const & colA, ColB const & colB )
	{
		return TestForSpecificOverlap<ColB, ColA>.test( colB, colA );
	}

	CollisionData testForGenericOverlap( ICollider const & colA, ICollider const & colB );

	Vector2D relativeColliderPositionToWorldPosition( Vector2D relativePosition, Vector2D worldPosition );

	//	Collision rectOverlap( ColliderAtPosition const & colA, ColliderAtPosition const & colB );

	/// @brief Tests if two colliders are overlapping. If the bounding boxes of the colliders aren't overlapping, the specific overlap tests aren't run.
	/// @tparam ColA
	/// @tparam ColB
	/// @param colA
	/// @param colB
	/// @return Data about the overlap (or lack thereof).
	template<class ColA, class ColB>
	CollisionData testForOverlap( ColA const & colA, ColB const & colB )
	{
		CollisionData result = testForGenericOverlap( colA, colB );
		if (result.intersectDistance != 0)
		{
			CollisionData specificResult = testSpecificOverlap<ColA, ColB>( colA, colB );
			if (specificResult.intersectDistance != 0)
			{
				result = specificResult;
			}
		}
		return result;
	}
}