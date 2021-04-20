#include "GameScene.h"
#include "Dino.h"
#include "WalkingDino.h"
GameScene::GameScene() : Scene( "Game" )
{
	Dino * dino = new Dino();
	_gameObjects[dino->ID()] = dino;

	WalkingDino * dinoWalking = new WalkingDino();
	_gameObjects[dinoWalking->ID()] = dinoWalking;
}

GameScene::~GameScene()
{}

void GameScene::update( SDL::Window * )
{

}