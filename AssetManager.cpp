#include "AssetManager.h"
#include "AnimatedTexture.h"
#include "SurfaceWrapper.h"
AssetManager::AssetManager()
{
	_loadAsset<Surface>( "Texture.Dino", "Assets/dino.png" );
	//	_assets["Texture.Dino"] = new Texture( "Assets/dino.png", renderer );

	_loadAsset<Surface>( "Texture.Debug.Rectangle", "Assets/rectangle.png" );

	_loadAsset<Surface>( "Texture.Debug.Circle", "Assets/circle.png" );

	AnimationProperties animProperties{};

	animProperties.frameCount = 10;
	animProperties.frameDurationMilliseconds = 200;

	_loadAsset<AnimatedSurface>( "Texture.Dino.Walking", "Assets/dino.walking.png", animProperties );

	//	_assets["Texture.Dino.Walking"] = new AnimatedTexture( "Assets/dino.walking.png", renderer, frameCount, frameDurationMilliseconds );

	_loadAsset<AnimatedSurface>( "Texture.Player.Idle", "Assets/player.idle.png", animProperties );
	_loadAsset<AnimatedSurface>( "Texture.Player.Walking", "Assets/player.walking.png", animProperties );
	_loadAsset<AnimatedSurface>( "Texture.Player.Running", "Assets/player.running.png", animProperties );
}

AssetManager::~AssetManager()
{}