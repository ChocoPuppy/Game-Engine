#pragma once
#include <string>
#include "PhysicsObject.h"
#include "Texture.h"
class RenderEngine;
class GameObject : public PhysicsObject
{
public:
	GameObject( std::string ID, std::string textureID, AssetManager * manager, RenderEngine * renderer );
	virtual ~GameObject();

	std::string ID();

	virtual void simulateAI( unsigned long millisecondsToSimulate, AssetManager * assets ) = 0;
	virtual void render( unsigned long millisecondsToSimulate, AssetManager * assets, RenderEngine * renderer );
protected:
	std::string _ID;

	SDL::Texture _texture;
};