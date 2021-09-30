#pragma once
#include "GameObject.h"
#include "GemType.h"
class GemObject : GameObject
{
	GemType _gemType;
	Coordinates _targetBoardPosition;
	float _lerpSpeed;
public:
	GemType getGemType();
	void setGemType( GemType newType );

	Vector2D getBoardPosition();
	float getLerpSpeed();
	void setLerpSpeed( float );
	void moveToBoardPosition( Coordinates position );
};