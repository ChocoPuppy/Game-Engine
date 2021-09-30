#pragma once
#include "Scene.h"
#include <set>
#include "TransversalDirections.h"
#include "Vector2D.h"
class GemObject;
class GemsScene : Scene
{
public:
	GemsScene();

	std::set<std::weak_ptr<GemObject>> getWorldGems();
	std::map<TransversalDirection, std::vector<std::weak_ptr<GemObject>>> getEdgeGems();

	Coordinates slideCoordinatesUntilCollision( Coordinates origin, Vector2D direction );
};