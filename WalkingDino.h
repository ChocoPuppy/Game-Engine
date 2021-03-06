#pragma once
#include "AnimatedGameObject.h"
class WalkingDino :
	public AnimatedGameObject
{
public:
	WalkingDino( std::string ID = "WalkingDino" );
	// Inherited via AnimatedGameObject
	virtual void simulateAI( unsigned long millisecondsToSimulate, AssetManager * assets ) override;
};
