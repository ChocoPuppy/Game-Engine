#pragma once
#include "AnimatedGameObject.h"
class WalkingDino :
	public AnimatedGameObject
{
public:
	WalkingDino( std::string ID );
	// Inherited via AnimatedGameObject
	virtual void simulateAI( unsigned long millisecondsToSimulate, AssetManager * manager ) override;
};
