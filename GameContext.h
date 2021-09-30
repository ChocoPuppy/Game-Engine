#pragma once
class AssetManager;
class Scene;
class InputManager;
class Editor;
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
	Editor * _editor;
	Collision::PhysicsEngine * _physicsEngine;
public:
	inline GameContext( AssetManager * assets, Scene * scene, InputManager * inputManager, Editor * editor, Collision::PhysicsEngine * physicsEngine ) : _assets( assets ), _scene( scene ), _inputManager( inputManager ), _editor( editor ), _physicsEngine( physicsEngine ) {}

	inline AssetManager * getAssets() noexcept { return _assets; };
	inline Scene * getScene() noexcept { return _scene; };
	inline InputManager * getInputManager() noexcept { return _inputManager; }
	inline Editor * getEditor() noexcept { return _editor; }
	inline Collision::PhysicsEngine * getPhysicsEngine() noexcept { return _physicsEngine; }
};