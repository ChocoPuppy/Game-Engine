#include "GameEngine.h"
#include "InputManager.h"
#include "GameScene.h"
#include "RenderEngine.h"
#include "PhysicsEngine.h"
int main()
{
	GameEngine engine = GameEngine();
	AssetManager assets = AssetManager( static_cast<SDL::Renderer *>( engine.getRenderer() ) );
	InputManager inputManager = InputManager();
	Scene * gameScene = new GameScene();
	Collision::PhysicsEngine physicsEngine = Collision::PhysicsEngine();

	GameContext context = GameContext( &assets, gameScene, &inputManager, &physicsEngine );
	while (true)
	{
		engine.update( context );
	}

	return 0;
}