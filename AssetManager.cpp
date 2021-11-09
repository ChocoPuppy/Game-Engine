#include "AssetManager.h"
#include "AnimatedTexture.h"
#include "SurfaceWrapper.h"
AssetManager::AssetManager()
{
	_loadAsset<Surface>( "Texture.Dino", "Assets/dino.png" );
	//	_assets["Texture.Dino"] = new Texture( "Assets/dino.png", renderer );

	_loadAsset<Surface>( "Texture.Debug.Rectangle", "Assets/rectangle.png" );

	_loadAsset<Surface>( "Texture.Debug.Circle", "Assets/circle.png" );

	_loadAsset<Surface>( "Texture.Dino.Walking", "Assets/dino.walking.png" );

	//	_assets["Texture.Dino.Walking"] = new AnimatedTexture( "Assets/dino.walking.png", renderer, frameCount, frameDurationMilliseconds );

	_loadAsset<Surface>( "Texture.Player.Idle", "Assets/player.idle.png" );
	_loadAsset<Surface>( "Texture.Player.Walking", "Assets/player.walking.png" );
	_loadAsset<Surface>( "Texture.Player.Running", "Assets/player.running.png" );
}

AssetManager::~AssetManager()
{}