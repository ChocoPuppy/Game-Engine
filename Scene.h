#pragma once
#include <string>
#include <vector>
#include <map>
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
	void addGameObject( GameObject * object );
	void removeGameObject( std::string ID );
	void removeGameObject( GameObject * object );
private:
	std::map<std::string, GameObject *> _gameObjects;
	std::string _ID;
};
