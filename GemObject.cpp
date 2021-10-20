#include "GemObject.h"
void GemObject::simulateAI( unsigned long, AssetManager * )
{}

void GemObject::_changeGemTextureTo( GemType::GemType type )
{
	_textureID = GemType::toTextureID( type );
}

void GemObject::_setGemType( GemType::GemType newType )
{
	_gemType = newType;
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

void GemObject::moveToBoardPosition( Coordinates position )
{
	transform()->position = { (double)position.x,(double)position.y };
}