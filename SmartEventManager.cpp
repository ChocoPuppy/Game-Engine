#include "SmartEventManager.h"
using namespace Event::SmartEvent;
std::unordered_set<std::unique_ptr<_ISmartEvent>> SmartEventManager::registeredEvents = std::unordered_set<std::unique_ptr<_ISmartEvent>>();