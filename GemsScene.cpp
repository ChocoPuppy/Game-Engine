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