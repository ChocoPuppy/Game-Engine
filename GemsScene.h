#pragma once
#include "Scene.h"
#include <set>
#include "TransversalDirections.h"
#include "Vector2D.h"
class GemObject;
class GemsScene : public Scene
{
public:
	GemsScene();

	Vector2D getMapBounds() const noexcept;

	std::set<std::weak_ptr<GemObject>> getWorldGems();
	std::map<TransversalDirection, std::vector<std::weak_ptr<GemObject>>> getEdgeGems();

	virtual void update( SDL::Window * window ) override;

	//	Coordinates slideCoordinatesUntilCollision( Coordinates origin, Vector2D direction );
private:
	static constexpr Vector2D _MAP_BOUNDS = { 10,10 };
};