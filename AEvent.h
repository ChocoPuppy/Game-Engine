#pragma once
#include <string>
#include <unordered_set>

#include "IObserver.h"
namespace Event {
	class AEvent {
		std::unordered_set<IObserver*> observers;
	protected:
		void update(std::string* message);
	public:
		void addObserver(IObserver* observer);
		void removeObserver(IObserver* observer);
	};
}
