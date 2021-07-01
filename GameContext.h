#pragma once
class AssetManager;
class Scene;

struct GameContext
{
private:
	AssetManager * _assets;
	Scene * _scene;
public:
	inline GameContext( AssetManager * assets, Scene * scene ) : _assets( assets ), _scene( scene ) {}

	inline AssetManager * getAssets() noexcept { return _assets; };
	inline Scene * getScene() noexcept { return _scene; };
};