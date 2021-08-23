#pragma once
#include "Vector2D.h"
#include "ICollider.h"
#include <type_traits>
namespace Collision
{
	struct CollisionData
	{
		float intersectDistance;
	};

	/// @brief A std::hash-like class for specialized overlap checking functions. This default implementation can't be called and will be skipped.
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

		bool test( ColliderA const & colliderA, ColliderB const & colliderB, CollisionData & data ) = delete;
	};

	namespace
	{
		template<class ColA, class ColB>
		using DoesSpecificOverlapTestForPairExist = std::is_default_constructible<TestForSpecificOverlap<ColA, ColB>>;
	}
	/// @brief If there's no specific overlap test for the types of those colliders, don't overwrite data.
	/// @tparam ColA One of the collider types.
	/// @tparam ColB The other collider type.
	/// @param colA One of the colliders.
	/// @param colB The other collider.
	/// @param data If return is true, will be overwritten with the collision data. Otherwise nothing happens to this
	/// @return If a specific overlap test for those collider types exists.
	template<class ColA, class ColB>
	typename std::enable_if_t<( !DoesSpecificOverlapTestForPairExist<ColA, ColB>::value && !DoesSpecificOverlapTestForPairExist<ColB, ColA>::value ), bool>
		testSpecificOverlap( ColA const & colA, ColB const & colB, CollisionData & data )
	{
		return false;
	}
	//Otherwise run the overlap test and return that.
	template<class ColA, class ColB>
	typename std::enable_if_t<DoesSpecificOverlapTestForPairExist<ColA, ColB>::value, bool>
		testSpecificOverlap( ColA const & colA, ColB const & colB, CollisionData & data )
	{
		data = TestForSpecificOverlap<ColA, ColB>.test( colA, colB );
		return true;
	}

	template<class ColA, class ColB>
	typename std::enable_if_t<DoesSpecificOverlapTestForPairExist<ColB, ColA>::value, bool>
		testSpecificOverlap( ColA const & colA, ColB const & colB, CollisionData & data )
	{
		data = TestForSpecificOverlap<ColB, ColA>.test( colB, colA );
		return true;
	}

	CollisionData testForGenericOverlap( ICollider const & colA, ICollider const & colB );

	Vector2D relativeColliderPositionToWorldPosition( Vector2D relativePosition, Vector2D worldPosition );

	//	Collision rectOverlap( ColliderAtPosition const & colA, ColliderAtPosition const & colB );

	/// @brief Tests if two colliders are overlapping. If the bounding boxes of the colliders aren't overlapping, the specific overlap tests aren't run.
	/// @tparam ColA One of the collider types.
	/// @tparam ColB The other collider type.
	/// @param colA One of the colliders.
	/// @param colB The other collider.
	/// @return Data about the overlap (or lack thereof).
	template<class ColA, class ColB>
	CollisionData testForOverlap( ColA const & colA, ColB const & colB )
	{
		CollisionData result = testForGenericOverlap( colA, colB );
		if (result.intersectDistance != 0)
		{
			//If a specific overlap test exists, results will be overwritten with that value, otherwise nothing happens.
			testSpecificOverlap<ColA, ColB>( colA, colB, result );
		}
		return result;
	}
}