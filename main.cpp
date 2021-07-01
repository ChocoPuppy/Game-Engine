#include "GameEngine.h"
#include "InputManager.h"
#include "GameScene.h"
int main()
{
	GameEngine engine = GameEngine();

	AssetManager assets = AssetManager( engine.getRenderer() );
	InputManager inputManager = InputManager();

	Scene * gameScene = new GameScene();

	GameContext context = GameContext( &assets, gameScene );
	while (true)
	{
		engine.update( context, &inputManager );
	}

	return 0;
}