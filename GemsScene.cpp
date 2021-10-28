#include "GemsScene.h"
#include "GemObject.h"
GemsScene::GemsScene() : Scene( "Gem scene" )
{
	auto * newGem = new GemObject( "Obj1" );
	newGem->setGemType( GemType::BLUE );
	newGem->rawMove( { 5,5 } );
	addGameObject( newGem );
}

Vector2D GemsScene::getMapBounds() const noexcept
{
	return _MAP_BOUNDS;
}

void GemsScene::update( SDL::Window * )
{}

Coordinates GemsScene::worldPosToGemsMapPos( Vector2D worldPos )
{
	Vector2D scaleTo = _WORLD_TO_MAP_POS_SCALE;
	scaleTo.x /= worldPos.x;
	scaleTo.y /= worldPos.y;
	Coordinates const GemsMapPos = Coordinates( scaleTo );
	return GemsMapPos;
}

Vector2D GemsScene::gemsMapPosToWorldPos( Coordinates gemsMapPos )
{
	Vector2D const floatingPointCoordinates{ (double)gemsMapPos.x,(double)gemsMapPos.y };
	Vector2D const worldPos = floatingPointCoordinates.dotProduct( _WORLD_TO_MAP_POS_SCALE );
	return worldPos;
}