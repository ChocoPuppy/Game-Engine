#include "Dino.h"

Dino::Dino() : GameObject( "Dino", "Texture.Dino" )
{
	transform()->position.x = 25;
	transform()->position.y = 25;
	transform()->scale.x = 100;
	transform()->scale.y = 100;

	velocity().y = 0.0000001;
	setRotationalVelocity( 0.0000001f );
}

void Dino::simulateAI( unsigned long, GameContext )
{}