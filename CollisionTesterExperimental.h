#pragma once
#include "ColliderTypes.h"
#include "CollisionTester.h"
#include "RectCollider2D.h"
#include "CircleCollider2D.h"
namespace Collision
{
	namespace Experimental
	{
		template<class FirstArgumentType, class TestType, class... OtherTypes>
		struct _testForSpecificOverlapSecondArgument
		{
			bool operator()( FirstArgumentType const * colA, ICollider const * colB, CollisionData * data )
			{
				bool result;
				auto colBAsType = dynamic_cast<std::add_pointer_t<std::add_const_t<TestType>>>( colA );
				if (colBAsType != nullptr)
				{
					result = testSpecificOverlap<FirstArgumentType, TestType>( *colA, *colBAsType, *data );
				}
				else
				{
					result = _testForSpecificOverlapSecondArgument<FirstArgumentType, OtherTypes...>()( colA, colB, data );
				}
				return result;
			}
		};

		template<class FirstArgumentType, class TestType>
		struct _testForSpecificOverlapSecondArgument<FirstArgumentType, TestType>
		{
			bool operator()( FirstArgumentType const * colA, ICollider const * colB, CollisionData * data )
			{
				bool result = false;
				auto colBAsType = dynamic_cast<std::add_pointer_t<std::add_const_t<TestType>>>( colA );
				if (colBAsType != nullptr)
				{
					result = testSpecificOverlap<FirstArgumentType, TestType>( *colA, *colBAsType, *data );
				}
				return result;
			}
		};

		template<class TestType, class... OtherTypes>
		struct _testForSpecificOverlapFirstArgument
		{
			bool operator() ( ICollider const * colA, ICollider const * colB, CollisionData * data )
			{
				bool result;
				auto colAAsType = dynamic_cast<std::add_pointer_t<std::add_const_t<TestType>>>( colA );
				if (colAAsType != nullptr)
				{
					result = _testForSpecificOverlapSecondArgumentStart<TestType, ColliderTypes>( colAAsType, colB, data );
				}
				else
				{
					result = _testForSpecificOverlapFirstArgument<OtherTypes...>()( colA, colB, data );
				}
				return result;
			}
		};

		template<class TestType>
		struct _testForSpecificOverlapFirstArgument<TestType>
		{
			bool operator()( ICollider const * colA, ICollider const * colB, CollisionData * data )
			{
				bool result = false;
				auto colAAsType = dynamic_cast<std::add_pointer_t<std::add_const_t<TestType>>>( colA );
				if (colAAsType != nullptr)
				{
					result = _testForSpecificOverlapSecondArgumentStart<TestType, ColliderTypes>( colAAsType, colB, data );
				}
				return result;
			}
		};

		template<typename ParPack = ColliderTypes>
		bool _testSpecificOverlapFirstArgumentStart( ICollider const * colA, ICollider const * colB, CollisionData * data )
		{
			auto tester = typename ParPack::template apply<_testForSpecificOverlapFirstArgument>();
			return tester( colA, colB, data );
		}

		template<class FirstArgumentType, typename ParPack = ColliderTypes>
		bool _testForSpecificOverlapSecondArgumentStart( FirstArgumentType const * colA, ICollider const * colB, CollisionData * data )
		{
			auto tester = typename ParPack::template Prefix<FirstArgumentType>::template apply<_testForSpecificOverlapSecondArgument>();
			return tester( colA, colB, data );
		}

		bool _testSpecificOverlap( ICollider const * colA, ICollider const * colB, CollisionData * data )
		{
			return _testSpecificOverlapFirstArgumentStart<ColliderTypes>( colA, colB, data );
		}

		CollisionData testForOverlap( ICollider const & colA, ICollider const & colB )
		{
			CollisionData result = testForGenericOverlap( colA, colB );
			if (result.intersectDistance != 0)
			{
				_testSpecificOverlap( &colA, &colB, &result );
			}
			return result;
		}
	}
}