#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <vector>
#include "Window.h"
class GameObject;

class Scene
{
public:
	Scene( std::string ID );
	~Scene();

	virtual void update( SDL::Window * window ) = 0;

	GameObject * getGameObject( std::string ID ) const;
	std::vector<GameObject *> getGameObjects() const;

	std::string getID() const;

protected:
	std::unordered_map<std::string, GameObject *> _gameObjects;
	std::string _ID;
};
