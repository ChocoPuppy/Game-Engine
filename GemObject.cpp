#include "GemObject.h"
void GemObject::simulateAI( unsigned long millisecondsToSimulate, AssetManager * assets )
{}

GemObject::GemObject( std::string ID ) : GameObject( ID, "" )
{}

GemType::GemType GemObject::getGemType() const
{
	return _gemType;
}

void GemObject::setGemType( GemType::GemType newType )
{
	_gemType = newType;
}

float GemObject::getLerpSpeed() const
{
	return _lerpSpeed;
}

void GemObject::setLerpSpeed( float speed )
{
	_lerpSpeed = speed;
}

void GemObject::moveToBoardPosition( Coordinates position )
{
	transform()->position = { position.x,position.y };
}