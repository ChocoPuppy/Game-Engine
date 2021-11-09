#pragma once
#include <string>
#include "PhysicsObject.h"
#include "TextureWrapper.h"
#include <memory>
class RenderEngine;
class GameObject : public PhysicsObject
{
public:
	GameObject( std::string ID, std::string textureID );
	virtual ~GameObject();

	std::string ID();

	virtual void simulateAI( unsigned long millisecondsToSimulate, AssetManager * assets ) = 0;
	virtual void render( unsigned long millisecondsToSimulate, AssetManager * assets, RenderEngine * renderer );
protected:
	std::string _getTextureID() const;
	void _setTextureID( std::string ID );

	Texture * _getTexture();

	void _switchIfTexturesChanged( AssetManager * assets, RenderEngine * renderer );
private:

	std::string _ID;
	std::string _textureID;
	std::unique_ptr<Texture> _texture;

	void refreshTexture( AssetManager * assets, RenderEngine * renderer );
};