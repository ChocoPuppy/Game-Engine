#include "GameEngine.h"
#include "InputManager.h"
#include "GameScene.h"
#include "RenderEngine.h"
#include "PhysicsEngine.h"
#include "Editor.h"
int main()
{
	GameEngine engine = GameEngine();
	AssetManager assets = AssetManager();
	InputManager inputManager = InputManager();
	Scene * gameScene = new GameScene();
	Collision::PhysicsEngine physicsEngine = Collision::PhysicsEngine();
	Editor editor = Editor( L"Gameu" );

	GameContext context = GameContext( &assets, gameScene, &inputManager, &editor, &physicsEngine );
	while (true)
	{
		engine.update( context );
	}

	return 0;
}