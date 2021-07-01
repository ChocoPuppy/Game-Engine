#pragma once
#include <string>
#include "AssetManager.h"
#include "Transform2D.h"
#include "Renderer.h"
class GameObject
{
public:
	GameObject( std::string ID, std::string textureID );
	~GameObject();

	std::string ID();

	virtual void simulateAI( unsigned long millisecondsToSimulate, AssetManager * assets ) = 0;
	virtual void simulatePhysics( unsigned long millisecondsToSimulate, AssetManager * assets );
	virtual void render( unsigned long millisecondsToSimulate, AssetManager * assets, SDL::Renderer * renderer );

	void rawMove( Vector2D toPosition );
protected:
	std::string _ID;
	std::string _textureID;

	Transform2D transform;
};