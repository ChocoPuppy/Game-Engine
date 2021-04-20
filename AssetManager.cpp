#include "AssetManager.h"
#include "AnimatedTexture.h"
AssetManager::AssetManager( SDL::Renderer * renderer )
{
	_assets["Texture.Dino"] = new Texture( "Assets/dino.png", renderer );

	constexpr int frameCount = 10;
	constexpr unsigned long frameDurationMilliseconds = 100;
	_assets["Texture.Dino.Walking"] = new AnimatedTexture( "Assets/dino.walking.png", renderer, frameCount, frameDurationMilliseconds );
}

AssetManager::~AssetManager()
{}