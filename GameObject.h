#pragma once
#include <string>
#include "PhysicsObject.h"
#include "Renderer.h"
class GameObject : public PhysicsObject
{
public:
	GameObject( std::string ID, std::string textureID );
	~GameObject();

	std::string ID();

	virtual void simulateAI( unsigned long millisecondsToSimulate, AssetManager * assets ) = 0;
	virtual void render( unsigned long millisecondsToSimulate, AssetManager * assets, SDL::Renderer * renderer );
protected:
	std::string _ID;
	std::string _textureID;
};