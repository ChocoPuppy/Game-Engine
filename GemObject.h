#pragma once
#include "GameObject.h"
#include "GemType.h"
class GemObject : GameObject
{
	GemType _gemType;

public:
	GemType getGemType();
	void setGemType( GemType newType );
};