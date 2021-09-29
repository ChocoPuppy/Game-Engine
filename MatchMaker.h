#pragma once
#include <set>
#include <map>
#include <memory>
#include <string>
class GemObject;
class MatchMaker
{
public:
	void findMatches( std::set<std::weak_ptr<GemObject>> board, std::set<std::string> updatedObjects )
	{
	}
};