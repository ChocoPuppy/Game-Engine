#include "AssetManager.h"
#include "AnimatedTexture.h"
AssetManager::AssetManager( SDL::Renderer * renderer )
{
	_loadAsset<Texture>( "Texture.Dino", "Assets/dino.png", renderer );
	//	_assets["Texture.Dino"] = new Texture( "Assets/dino.png", renderer );

	constexpr int frameCount = 10;
	constexpr unsigned long frameDurationMilliseconds = 100;
	_loadAsset<AnimatedTexture>( "Texture.Dino.Walking", "Assets/dino.walking.png", renderer, frameCount, frameDurationMilliseconds );
	//	_assets["Texture.Dino.Walking"] = new AnimatedTexture( "Assets/dino.walking.png", renderer, frameCount, frameDurationMilliseconds );
}

AssetManager::~AssetManager()
{}