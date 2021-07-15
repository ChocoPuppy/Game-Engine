#pragma once
#include <unordered_set>
#include <memory>
namespace Event
{
	namespace SmartEvent
	{
		class _ISmartEvent
		{
			//			_ISmartEvent( _ISmartEvent const & ) = delete;
		public:
			virtual ~_ISmartEvent() = default;
		};
	}
}
