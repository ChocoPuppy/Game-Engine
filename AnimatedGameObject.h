#pragma once
#include "GameObject.h"
class AnimatedGameObject :
	public GameObject
{
public:
	AnimatedGameObject( std::string id, std::string textureId );
	virtual void render( unsigned long millisecondsToSimulate, AssetManager * assets, RenderEngine * renderer ) override;
};
