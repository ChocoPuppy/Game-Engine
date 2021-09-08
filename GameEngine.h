#pragma once
#include "SDLBase.h"

#include "AssetManager.h"

#include <ostream>
#include "Scene.h"

#include "Button.h"
#include "ButtonEvent.h"
#include "ExitHandler.h"
#include "GameContext.h"
class RenderEngine;
class GameEngine
{
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

	ExitHandler _exitInputHandler;

	RenderEngine * _renderer;
	SDL::Window * _window;

	GameEngine();
	~GameEngine();

	void setMaxFPS( float desiredFPS );

	void simulate( unsigned long millisecondsToSimulate, GameContext context );
	void simulateAI( unsigned long millisecondsToSimulate, GameContext context );
	void simulatePhysics( unsigned long millisecondsToSimulate, GameContext context );
	void render( unsigned long millisecondsToSimulate, GameContext context );
	void updateInput( unsigned long millisecondsToSimulate, GameContext context );

	void initializeSDL();
	void generateWindow();
	void generateRenderer();

	static std::vector<GameObject *> _sortFromLowestToHighestY( std::vector<GameObject *> list );
public:
	void update( GameContext context );

	RenderEngine * getRenderer();
	SDL::Window * getWindow();

	unsigned long getMaxFPS();
private:
	void _updateEditor( GameContext context );
};
