#pragma once
//This is the header you probably want to include. This just exists to prevent a circular dependency since InputManager stores the ButtonEvents, but the ButtonEvents need to have access to the InputManager beforehand so they can be templated.
#include "_ButtonEvent.h"
#include "InputManager.h"