#pragma once
class AssetManager;
class Scene;
class InputManager;
class PhysicsEngine;
struct GameContext
{
private:
	AssetManager * _assets;
	Scene * _scene;
	InputManager * _inputManager;
	PhysicsEngine * _physicsEngine;
public:
	inline GameContext( AssetManager * assets, Scene * scene, InputManager * inputManager, PhysicsEngine * physicsEngine ) : _assets( assets ), _scene( scene ), _inputManager( inputManager ), _physicsEngine( physicsEngine ) {}

	inline AssetManager * getAssets() noexcept { return _assets; };
	inline Scene * getScene() noexcept { return _scene; };
	inline InputManager * getInputManager() noexcept { return _inputManager; }
	inline PhysicsEngine * getPhysicsEngine() noexcept { return _physicsEngine; }
};