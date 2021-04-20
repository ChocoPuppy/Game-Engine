#pragma once
#include "GameObject.h"
class Dino : public GameObject
{
public:
	Dino();
	// Inherited via GameObject
	virtual void simulateAI( unsigned long millisecondsToSimulate, AssetManager * assets ) override;
};
