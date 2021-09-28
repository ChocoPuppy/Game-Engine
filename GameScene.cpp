#include "GameScene.h"
#include "Dino.h"
#include "WalkingDino.h"
#include "Player.h"
GameScene::GameScene() : Scene( "Game" )
{
	Dino * dino = new Dino();
	addGameObject( dino );

	WalkingDino * dinoWalking = new WalkingDino( "WalkingDino" );
	addGameObject( dinoWalking );

	/*	WalkingDino * dinoWalking2 = new WalkingDino( "WalkingDino2" );
		dinoWalking2->rawMove( { 200, 200 } );
		_gameObjects[dinoWalking2->ID()] = dinoWalking2;*/

	Player * player = new Player( "Player" );
	addGameObject( player );
}

GameScene::~GameScene()
{}

void GameScene::update( SDL::Window * )
{}