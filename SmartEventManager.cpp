#include "SmartEventManager.h"
using namespace Event::SmartEvent;
std::unordered_map<std::type_index, std::unique_ptr<_ISmartEvent>> SmartEventManager::events = std::unordered_map<std::type_index, std::unique_ptr<_ISmartEvent>>();