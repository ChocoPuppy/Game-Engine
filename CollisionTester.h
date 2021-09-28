#pragma once
#include "Vector2D.h"
#include "ICollider.h"
#include <type_traits>
#include <typeinfo>
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
	struct TestForSpecificOverlap
	{
		TestForSpecificOverlap() = delete;
		TestForSpecificOverlap( TestForSpecificOverlap const & ) = delete;
		TestForSpecificOverlap( TestForSpecificOverlap && ) = delete;
		void operator=( TestForSpecificOverlap const & ) = delete;
		void operator=( TestForSpecificOverlap && ) = delete;

		void operator()( ColliderA const & colliderA, ColliderB const & colliderB, CollisionData & data ) = delete;
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
		TestForSpecificOverlap<ColA, ColB>()( colA, colB, data );
		return true;
	}
	//Otherwise run the overlap test with the values flipped (since overlap testing is symmetrical).
	template<class ColA, class ColB>
	typename std::enable_if_t<DoesSpecificOverlapTestForPairExist<ColB, ColA>::value && !DoesSpecificOverlapTestForPairExist<ColA, ColB>::value, bool>
		testSpecificOverlap( ColA const & colA, ColB const & colB, CollisionData & data )
	{
		bool result = testSpecificOverlap( colB, colA, data );

		return result;
	}

	CollisionData testForGenericOverlap( ICollider const & colA, ICollider const & colB );

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
			//If a specific overlap test exists, results will most likely be overwritten with values from the more accurate specific test, otherwise nothing happens.
			bool specificOverlapTestExists = testSpecificOverlap<ColA, ColB>( colA, colB, result );
			if (!specificOverlapTestExists)
			{
				std::cout << "Warning: no specific overlap test exists between a " << typeid( ColA )::name << " and a " << typeid( ColB )::name << ". Bounding box check used instead as collision data.";
			}
		}
		return result;
	}
}