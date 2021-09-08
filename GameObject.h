#pragma once
#include <string>
#include "PhysicsObject.h"
class RenderEngine;
class GameObject : public PhysicsObject
{
public:
	GameObject( std::string ID, std::string textureID );
	virtual ~GameObject();

	std::string ID();
	std::string textureID();

	virtual void simulateAI( unsigned long millisecondsToSimulate, AssetManager * assets ) = 0;
	virtual void render( unsigned long millisecondsToSimulate, AssetManager * assets, RenderEngine * renderer );
protected:
	std::string _ID;
	std::string _textureID;
};