#include "GameEngine.h"
#include "InputManager.h"
#include "GemsScene.h"
#include "RenderEngine.h"
#include "PhysicsEngine.h"
#include "Editor.h"
int main()
{
	GameEngine engine = GameEngine();
	AssetManager assets = AssetManager( static_cast<SDL::Renderer *>( engine.getRenderer() ) );
	InputManager inputManager = InputManager();
	Scene * gameScene = new GemsScene();
	Collision::PhysicsEngine physicsEngine = Collision::PhysicsEngine();
	Editor editor = Editor( L"Gameu" );

	GameContext context = GameContext( &assets, gameScene, &inputManager, &editor, &physicsEngine );
	while (true)
	{
		engine.update( context );
	}

	return 0;
}