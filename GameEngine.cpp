#include "GameEngine.h"

#include <chrono>
#include <thread>
#include <algorithm>

#include <SDL_image.h>

#include "SDLMain.h"
#include "Texture.h"
#include "SDLError.h"
#include "Dino.h"
#include "WalkingDino.h"
#include "Size.h"
#include "Color.h"
#include "Coordinates.h"
#include "InputManager.h"

using std::cout;
using std::cerr;
using std::endl;

GameEngine::GameEngine()
{
	initializeSDL();

	generateWindow();

	generateRenderer();

	exitInputHandler = ExitInputHandler();
}

GameEngine::~GameEngine()
{}

void GameEngine::setMaxFPS( float )
{
	//	minTimeBetweenFrames = 1 / desiredFPS;
	//	maxFPS = desiredFPS;
}

void GameEngine::update( GameContext context, InputManager * input )
{
	frameStartTimeMilliseconds = SDL::getTicks();
	const unsigned long previousFrameDurationMilliseconds = frameEndTimeMilliseconds - frameStartTimeMilliseconds;
	//	cout << frameEndTimeMilliseconds << endl;
	//	cout << frameStartTimeMilliseconds << endl;
	//	cout << previousFrameDurationMilliseconds << endl << endl;
	simulate( previousFrameDurationMilliseconds, context, input );
	const unsigned long currentTimeMilliseconds = SDL::getTicks();
	const unsigned long frameDurationMilliseconds = currentTimeMilliseconds - frameStartTimeMilliseconds;
	frameEndTimeMilliseconds = SDL::getTicks();

	if (frameDurationMilliseconds < minimumFrameTimeMilliseconds)
	{
		const std::chrono::milliseconds timeToSleepBeforeNextFrame( minimumFrameTimeMilliseconds - frameDurationMilliseconds );
		std::this_thread::sleep_for( timeToSleepBeforeNextFrame );
	}

	//	cout << frameEndTimeMilliseconds - frameStartTimeMilliseconds << endl;
}

SDL::Renderer * GameEngine::getRenderer()
{
	return _renderer;
}

SDL::Window * GameEngine::getWindow()
{
	return _window;
}

inline unsigned long GameEngine::getMaxFPS()
{
	return maxFPS;
}

void GameEngine::simulate( unsigned long millisecondsToSimulate, GameContext context, InputManager * input )
{
	simulateAI( millisecondsToSimulate, context );
	simulatePhysics( millisecondsToSimulate, context );
	render( millisecondsToSimulate, context );
	updateInput( millisecondsToSimulate, context, input );
}

void GameEngine::simulateAI( unsigned long, GameContext )
{
	//	cout << "Aeh" << endl;
}

void GameEngine::simulatePhysics( unsigned long, GameContext )
{
	//	cout << "Pheh" << endl;
}

void GameEngine::render( unsigned long millisecondsToSimulate, GameContext context )
{
	//	cout << "Reh" << endl;
	SDL::Renderer * renderer = getRenderer();

	renderer->clear();

	constexpr Uint8 red = 255, green = 0, blue = 255, alpha = 255;

	renderer->setDrawColor( Color( red, green, blue, alpha ) );
	//	Texture * dino = assets->getAsset<Texture>( "Texture.Dino" );
	for (GameObject * obj : context.getScene()->getGameObjects())
	{
		obj->render( millisecondsToSimulate, context.getAssets(), renderer );
	}
	renderer->present();
}

void GameEngine::updateInput( unsigned long, GameContext, InputManager * input )
{
	input->updateInputs();
}

void GameEngine::generateWindow()
{
	constexpr int windowPosX = 300;
	constexpr int windowPosY = 300;
	constexpr int windowHeight = 600;
	constexpr int windowWidth = 600;

	SDL::WindowBuilder windowBuilder = SDL::WindowBuilder();
	windowBuilder.setSize( Size( windowHeight, windowWidth ) );
	windowBuilder.setPosition( Coordinates( windowPosX, windowPosY ) );
	windowBuilder.setTitle( "Gameu" );

	_window = windowBuilder.getWindow();
}

void GameEngine::generateRenderer()
{
	_renderer = new SDL::Renderer( getWindow() );
}

void GameEngine::initializeSDL()
{
	const int initResults = SDL_Init( SDL_INIT_VIDEO );

	if (initResults != SDL::SDLGenericSuccessCode)
	{
		SDL::passSDLError( "Failed to initialize SDL." );
	}

	const int IMGinitResults = IMG_Init( IMG_INIT_PNG );
	constexpr int IMGinitSuccess = IMG_INIT_PNG;

	if (IMGinitResults != IMGinitSuccess)
	{
		SDL::passSDLError( "Failed to initialize SDL image" );
	}
}

void GameEngine::ExitInputHandler::update( InputManager *, Button button )
{
	switch (button) //Basically if (button != Button::QUIT) return; but slightly quicker, since events are probably something you want to get through as quick as possible if they don't actually qualify.
	{
	case Button::QUIT:
		break;
	default:
		return;
	}
	std::cout << "Ending..." << endl;
}

GameEngine::GameContext::GameContext( AssetManager * assets, Scene * scene )
{
	_assets = assets;
	_scene = scene;
}

AssetManager * GameEngine::GameContext::getAssets()
{
	return _assets;
}

Scene * GameEngine::GameContext::getScene()
{
	return _scene;
}