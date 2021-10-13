#include "AssetManager.h"
#include "AnimatedTexture.h"
AssetManager::AssetManager( SDL::Renderer * renderer )
{
	_loadAsset<Texture>( "Texture.Dino", "Assets/dino.png", renderer );
	//	_assets["Texture.Dino"] = new Texture( "Assets/dino.png", renderer );

	_loadAsset<Texture>( "Texture.Debug.Rectangle", "Assets/rectangle.png", renderer );
	_loadAsset<Texture>( "Texture.Debug.Circle", "Assets/circle.png", renderer );

	_loadAsset<Texture>( "Texture.Gem.Red", "Assets/gem.red.png", renderer );
	_loadAsset<Texture>( "Texture.Gem.Blue", "Assets/gem.blue.png", renderer );
	_loadAsset<Texture>( "Texture.Gem.Green", "Assets/gem.green.png", renderer );
	_loadAsset<Texture>( "Texture.Gem.White", "Assets/gem.white.png", renderer );
	_loadAsset<Texture>( "Texture.Gem.Bomb", "Assets/gem.bomb.png", renderer );
	_loadAsset<Texture>( "Texture.Gem.Unknown", "Assets/gem.unknown.png", renderer );

	constexpr int frameCount = 10;
	constexpr unsigned long frameDurationMilliseconds = 100;
	_loadAsset<AnimatedTexture>( "Texture.Dino.Walking", "Assets/dino.walking.png", renderer, frameCount, frameDurationMilliseconds );
	//	_assets["Texture.Dino.Walking"] = new AnimatedTexture( "Assets/dino.walking.png", renderer, frameCount, frameDurationMilliseconds );

	_loadAsset<AnimatedTexture>( "Texture.Player.Idle", "Assets/player.idle.png", renderer, frameCount, frameDurationMilliseconds );
	_loadAsset<AnimatedTexture>( "Texture.Player.Walking", "Assets/player.walking.png", renderer, frameCount, frameDurationMilliseconds );
	_loadAsset<AnimatedTexture>( "Texture.Player.Running", "Assets/player.running.png", renderer, frameCount, frameDurationMilliseconds );
}

AssetManager::~AssetManager()
{}