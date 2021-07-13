#pragma once

#include <map>
#include <iostream>

#include "Asset.h"
#include "Renderer.h"

class AssetManager
{
public:
	AssetManager( SDL::Renderer * renderer );
	~AssetManager();
	template<class AssetType>
	AssetType * getAsset( std::string id );
private:
	template<class AssetType, typename... ConstructorArgs>
	void _loadAsset( std::string ID, std::string path, ConstructorArgs... args );

	std::map<std::string, Asset *> _assets;
};

template<class AssetType>
AssetType * AssetManager::getAsset( std::string id )
{
	if (_assets.find( id ) == _assets.end())
	{
		std::cerr << "Attempted to find an asset that was not loaded. ID: " << id << std::endl;
		exit( 1 );
	}
	AssetType * target = dynamic_cast<AssetType *>( _assets[id] );
	if (target == NULL)
	{
		std::cerr << "Attempted to convert Asset to invalid type. ID: " << id << std::endl;
		exit( 1 );
	}
	return target;
}

template<class AssetType, typename ...ConstructorArgs>
void AssetManager::_loadAsset( std::string ID, std::string path, ConstructorArgs ...constructorArgs )
{
	AssetType * temp = new AssetType( ID, path, constructorArgs... );
	Asset * newAsset = static_cast<Asset *>( temp );
	_assets[newAsset->getID()] = newAsset;
}
