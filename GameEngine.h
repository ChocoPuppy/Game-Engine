#pragma once
#include "SDLBase.h"

#include "AssetManager.h"

#include <ostream>
#include "Scene.h"

#include "SDLVideo.h"

#include "ExitHandler.h"
#include "Button.h"
#include "ButtonEvent.h"
class InputManager;

class GameEngine
{
public:
	struct GameContext
	{
	private:
		AssetManager * _assets;
		Scene * _scene;
	public:
		GameContext( AssetManager * assets, Scene * scene );

		AssetManager * getAssets();
		Scene * getScene();
	};
private:
	friend int main();

	bool running = true;
	static constexpr unsigned long millisecondsPerSecond = 1000;
	unsigned long maxFPS = 30;
	unsigned long minimumFrameTimeMilliseconds = millisecondsPerSecond / maxFPS;

	unsigned long millisecondsSinceLastUpdate = 0;
	unsigned long frameStartTimeMilliseconds = 0;
	unsigned long frameEndTimeMilliseconds = frameStartTimeMilliseconds;
	//	float minTimeBetweenFrames;

	//	float timeSinceLastFrame;

	ExitHandler _exitHandler;

	SDL::Renderer * _renderer;
	SDL::Window * _window;

	GameEngine();
	~GameEngine();

	void setMaxFPS( float desiredFPS );

	void simulate( unsigned long millisecondsToSimulate, GameContext context, InputManager * input );
	void simulateAI( unsigned long millisecondsToSimulate, GameContext context );
	void simulatePhysics( unsigned long millisecondsToSimulate, GameContext context );
	void render( unsigned long millisecondsToSimulate, GameContext context );
	void updateInput( unsigned long millisecondsToSimulate, GameContext context, InputManager * input );

	void initializeSDL();
	void generateWindow();
	void generateRenderer();
public:
	void update( GameContext context, InputManager * input );

	SDL::Renderer * getRenderer();
	SDL::Window * getWindow();

	unsigned long getMaxFPS();
};
