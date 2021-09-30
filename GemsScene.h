#pragma once
#include "Scene.h"
#include <set>
class GemObject;
class GemsScene : Scene
{
public:
	GemsScene();

	std::set<GemObject *> getWorldGems();
};