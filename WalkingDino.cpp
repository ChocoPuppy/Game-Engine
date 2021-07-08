#include "WalkingDino.h"

WalkingDino::WalkingDino() : AnimatedGameObject( "WalkingDino", "Texture.Dino.Walking" )
{
	transform().position.x() = 75;
	transform().position.y() = 75;
	transform().scale.x() = 100;
	transform().scale.y() = 100;

	velocity() = Vector2D( 0.02f, 0 );
}

void WalkingDino::simulateAI( unsigned long, AssetManager * )
{}