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
	//Gems are stored leftmost/upmost to rightmost/downmost
	std::vector<std::weak_ptr<GemObject>> getEdgeGems( TransversalDirection direction );

	virtual void update( SDL::Window * window ) override;

	static Coordinates worldPosToGemsMapPos( Vector2D worldPos );
	static Vector2D gemsMapPosToWorldPos( Coordinates gemsMapPos );

	//	Coordinates slideCoordinatesUntilCollision( Coordinates origin, Vector2D direction );
private:
	static constexpr Vector2D _MAP_BOUNDS = { 10,10 };
	static constexpr Vector2D _WORLD_TO_MAP_POS_SCALE = { 30,30 };
	std::set<std::weak_ptr<GemObject>> _worldGems;
	std::map<TransversalDirection, std::vector<std::weak_ptr<GemObject>>> _edgeGems;
};