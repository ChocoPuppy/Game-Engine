#include "Scene.h"
#include "GameObject.h"
#include <iostream>
Scene::Scene( std::string ID )
{
	_ID = ID;
}

Scene::~Scene() = default;

GameObject * Scene::getGameObject( std::string ID ) const
{
	if (_gameObjects.find( ID ) == _gameObjects.end())
	{
		std::cout << "Failed to find gameobject of ID: " << ID << " in scene ID: " << getID() << std::endl;
		exit( 1 );
	}
	return _gameObjects.at( ID );
}

std::vector<GameObject *> Scene::getGameObjects() const
{
	std::vector<GameObject *> objects = std::vector<GameObject *>();

	for (auto & keyPair : _gameObjects)
	{
		objects.push_back( keyPair.second );
	}
	return objects;
}

std::string Scene::getID() const
{
	return _ID;
}

void Scene::addGameObject( GameObject * object )
{
	_gameObjects.emplace( object->ID(), object );
}

void Scene::removeGameObject( std::string ID )
{
	_gameObjects.erase( ID );
}

void Scene::removeGameObject( GameObject * object )
{
	removeGameObject( object->ID() );
}