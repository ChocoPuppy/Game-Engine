#pragma once
#include "Scene.h"
class GameScene :
	public Scene
{
public: 
	GameScene();
	~GameScene();

	virtual void update( SDL::Window * window ) override;
};

