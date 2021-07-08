#include "Dino.h"

Dino::Dino() : GameObject( "Dino", "Texture.Dino" )
{
	transform.position.x() = 75;
	transform.position.y() = 75;
	transform.scale.x() = 100;
	transform.scale.y() = 100;
}

void Dino::simulateAI( unsigned long, AssetManager * )
{}