#pragma once
#include "ColliderTypes.h"
#include "CollisionTester.h"
#include "RectCollider2D.h"
#include "CircleCollider2D.h"
namespace Collision
{
	namespace Experimental
	{
		template<class... TestTypes>
		class _testAnyApplicableSpecificOverlap
		{
			template<class TestType, class... OtherTypes>
			struct _testFirstArgument
			{
				bool operator()( ICollider const & colA, ICollider const & colB, CollisionData & data ) const
				{
					bool result = _testFirstArgument<TestType>()( colA, colB, data );
					if (!result)
					{
						result = _testFirstArgument<OtherTypes...>()( colA, colB, data );
					}
					return result;
				}
			};

			template<class TestType>
			struct _testFirstArgument<TestType>
			{
				bool operator()( ICollider const & colA, ICollider const & colB, CollisionData & data ) const
				{
					bool result = false;
					auto colAAsType = _castToConstPointer<TestType>( &colA );
					if (_isValidPointer( colAAsType ))
					{
						auto testSecondArgument = _testSecondArgument<TestType, TestTypes...>();
						result = testSecondArgument( *colAAsType, colB, data );
					}
					return result;
				}
			};

			template<class FirstArgumentType, class TestType, class... OtherTypes>
			struct _testSecondArgument
			{
				bool operator()( FirstArgumentType const & colA, ICollider const & colB, CollisionData & data ) const
				{
					bool result = _testSecondArgument<FirstArgumentType, TestType>()( colA, colB, data );
					if (!result)
					{
						result = _testSecondArgument<FirstArgumentType, OtherTypes...>()( colA, colB, data );
					}
					return result;
				}
			};

			template<class FirstArgumentType, class TestType>
			struct _testSecondArgument<FirstArgumentType, TestType>
			{
				bool operator()( FirstArgumentType const & colA, ICollider const & colB, CollisionData & data ) const
				{
					bool result = false;
					auto colBAsType = _castToConstPointer<TestType>( &colB );
					if (_isValidPointer( colBAsType ))
					{
						result = testSpecificOverlap < FirstArgumentType, TestType>( colA, *colBAsType, data );
					}
					return result;
				}
			};

		public:
			bool operator()( ICollider const & colA, ICollider const & colB, CollisionData & data ) const
			{
				return _testFirstArgument<TestTypes...>()( colA, colB, data );
			}
		};

		using _testForSpecificOverlapWithAllTypes = ColliderTypes::template apply<_testAnyApplicableSpecificOverlap>;

		template<class TestType>
		static bool _isValidPointer( TestType const * testConversion )
		{
			return testConversion != nullptr;
		}

		template<class TestType>
		static TestType const * _castToConstPointer( ICollider const * collider )
		{
			return dynamic_cast<std::add_pointer_t<std::add_const_t<TestType>>>( collider );
		}

		bool _testSpecificOverlap( ICollider const & colA, ICollider const & colB, CollisionData & data )
		{
			static const auto test = _testForSpecificOverlapWithAllTypes();
			return test( colA, colB, data );
		}

		CollisionData testForOverlap( ICollider const & colA, ICollider const & colB )
		{
			CollisionData result = testForGenericOverlap( colA, colB );
			if (result.intersectDistance != 0)
			{
				_testSpecificOverlap( colA, colB, result );
			}
			return result;
		}
	}
}