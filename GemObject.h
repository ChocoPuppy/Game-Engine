#pragma once
#include "GameObject.h"
#include "GemType.h"
#include "Lerp.h"
#include <optional>

class GemObject : public GameObject
{
	GemType::GemType _gemType;
	std::optional<Lerp<>> _lerp;
	float _lerpSpeed;
	void _changeGemTextureTo( GemType::GemType type );
	void _setGemType( GemType::GemType newType );

	void _endLerp();
public:
	GemObject( std::string ID );

	GemType::GemType getGemType() const;
	void setGemType( GemType::GemType newType );

	float getLerpSpeed() const;
	void setLerpSpeed( float speed );
	void lerpToPosition( Vector2D position );

	virtual void simulateAI( unsigned long millisecondsToSimulate, AssetManager * assets ) override;
};