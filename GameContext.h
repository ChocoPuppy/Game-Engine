#pragma once
class AssetManager;
class Scene;
class InputManager;
namespace Collision
{
	class PhysicsEngine;
}

struct GameContext
{
private:
	AssetManager * _assets;
	Scene * _scene;
	InputManager * _inputManager;
	Collision::PhysicsEngine * _physicsEngine;
public:
	inline GameContext( AssetManager * assets, Scene * scene, InputManager * inputManager, Collision::PhysicsEngine * physicsEngine ) : _assets( assets ), _scene( scene ), _inputManager( inputManager ), _physicsEngine( physicsEngine ) {}

	inline AssetManager * getAssets() noexcept { return _assets; };
	inline Scene * getScene() noexcept { return _scene; };
	inline InputManager * getInputManager() noexcept { return _inputManager; }
	inline Collision::PhysicsEngine * getPhysicsEngine() noexcept { return _physicsEngine; }
};