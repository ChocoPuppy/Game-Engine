#include "WalkingDino.h"

WalkingDino::WalkingDino( std::string ID ) : AnimatedGameObject( ID, "Texture.Dino.Walking" )
{
	transform()->position.x = 200;
	transform()->position.y = 75;
	transform()->scale.x = 100;
	transform()->scale.y = 100;
}

void WalkingDino::simulateAI( unsigned long, AssetManager * )
{}