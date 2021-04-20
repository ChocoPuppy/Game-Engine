#pragma once
#include <string>
namespace Event {
	class IObserver {
		friend class AEvent;
	private:
		virtual void update(std::string* message) = 0;
	};
}
