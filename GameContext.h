#pragma once
class AssetManager;
class Scene;
class InputManager;
struct GameContext
{
private:
	AssetManager * _assets;
	Scene * _scene;
	InputManager * _inputManager;
public:
	inline GameContext( AssetManager * assets, Scene * scene, InputManager * inputManager ) : _assets( assets ), _scene( scene ), _inputManager( inputManager ) {}

	inline AssetManager * getAssets() noexcept { return _assets; };
	inline Scene * getScene() noexcept { return _scene; };
	inline InputManager * getInputManager() noexcept { return _inputManager; }
};