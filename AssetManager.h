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
	AssetType * target = (AssetType *)_assets[id];
	if (target == NULL)
	{
		std::cerr << "Attempted to convert Asset to invalid type. ID: " << id << std::endl;
		exit( 1 );
	}
	return target;
}
