#pragma once
#include "GameObject.h"
#include "GemType.h"
class GemObject : public GameObject
{
	GemType::GemTypes _gemType;
	Coordinates _targetBoardPosition;
	float _lerpSpeed;

	void _changeGemTextureTo( GemType::GemType type );
public:
	GemObject( std::string ID );

	GemType::GemType getGemType() const;
	void setGemType( GemType::GemType newType );

	float getLerpSpeed() const;
	void setLerpSpeed( float speed );
	void moveToBoardPosition( Coordinates position );

	virtual void simulateAI( unsigned long millisecondsToSimulate, AssetManager * assets ) override;
};