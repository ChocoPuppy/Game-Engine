#pragma once
#include "GameObject.h"
class AnimatedGameObject :
	public GameObject
{
public:
	AnimatedGameObject( std::string id, std::string textureId, AssetManager * assets, RenderEngine * renderer );
	virtual void render( unsigned long millisecondsToSimulate, RenderEngine * renderer ) override;
};
