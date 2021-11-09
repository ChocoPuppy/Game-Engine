#include "AnimatedGameObject.h"
#include <iostream>

#include "AnimatedTexture.h"

AnimatedGameObject::AnimatedGameObject( std::string ID, std::string textureID ) : GameObject( ID, textureID )
{}

void AnimatedGameObject::render( unsigned long millisecondsToSimulate, AssetManager * assets, RenderEngine * renderer )
{
	_switchIfTexturesChanged( assets, renderer );
	AnimatedTexture * texture = static_cast<AnimatedTexture *>( _getTexture() );
	//	std::cout << "Animated game object running" << std::endl;
	texture->updateFrame( (unsigned long)millisecondsToSimulate );
	GameObject::render( millisecondsToSimulate, assets, renderer );
}