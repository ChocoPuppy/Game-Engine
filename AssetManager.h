#pragma once

#include <map>
#include <iostream>

#include "Asset.h"
#include "Renderer.h"

class AssetManager
{
public:
	AssetManager();
	~AssetManager();

	template<class AssetType>
	AssetType const * getAsset( std::string id ) const;
	template<class AssetType>
	AssetType * getAsset( std::string id );
private:
	template<class AssetType, typename... ConstructorArgs>
	void _loadAsset( std::string ID, std::string path, ConstructorArgs... args );

	std::map<std::string, Asset *> _assets;
};

template<class AssetType>
inline AssetType const * AssetManager::getAsset( std::string id ) const
{
	if (_assets.find( id ) == _assets.end())
	{
		std::cerr << "Attempted to find an asset that was not loaded. ID: " << id << std::endl;
		exit( 1 );
	}
	AssetType const * target = dynamic_cast<AssetType *>( _assets.at( id ) );
	if (target == NULL)
	{
		std::cerr << "Attempted to convert Asset to invalid type. ID: " << id << std::endl;
		exit( 1 );
	}
	return target;
}

template<class AssetType>
AssetType * AssetManager::getAsset( std::string id )
{
	return const_cast<AssetType *>( ( (AssetManager const *)this )->getAsset<AssetType>( id ) );
}

template<class AssetType, typename ...ConstructorArgs>
void AssetManager::_loadAsset( std::string ID, std::string path, ConstructorArgs ...constructorArgs )
{
	AssetType * temp = new AssetType( ID, path, constructorArgs... );
	Asset * newAsset = static_cast<Asset *>( temp );
	_assets[newAsset->getID()] = newAsset;
}
