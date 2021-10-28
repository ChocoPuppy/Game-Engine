#include "GemObject.h"
void GemObject::simulateAI( unsigned long millisecondsToSimulate, AssetManager * )
{
	if (_lerp)
	{
		if (_lerp->isComplete())
		{
			//Snap back to the end if the lerp has overshot it's goal.
			rawMove( _lerp->target );
			_endLerp();
		}
		else
		{
			float const moveBy = (float)millisecondsToSimulate * getLerpSpeed();
			float const moveByToSeconds = moveBy / 1000.0f;
			_lerp->update( moveByToSeconds );
			rawMove( _lerp->getCurrentPoint() );
		}
	}
}

void GemObject::_changeGemTextureTo( GemType::GemType type )
{
	_textureID = GemType::toTextureID( type );
}

void GemObject::_setGemType( GemType::GemType newType )
{
	_gemType = newType;
}

void GemObject::_endLerp()
{
	_lerp.reset();
}

GemObject::GemObject( std::string ID ) : GameObject( ID, "" )
{
	transform()->scale = { 30,30 };
}

GemType::GemType GemObject::getGemType() const
{
	return _gemType;
}

void GemObject::setGemType( GemType::GemType newType )
{
	_changeGemTextureTo( newType );
	_setGemType( newType );
}

float GemObject::getLerpSpeed() const
{
	return _lerpSpeed;
}

void GemObject::setLerpSpeed( float speed )
{
	_lerpSpeed = speed;
}

void GemObject::lerpToPosition( Vector2D position )
{
	Lerp<> newLerp = Lerp<>();
	newLerp.origin = transform()->position;
	newLerp.target = position;
	_lerp = newLerp;
}