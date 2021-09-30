#pragma once
#include <set>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include "TransversalDirections.h"
class GemScene;
class MatchMaker
{
	static constexpr float MAX_ADJACENCY_DISTANCE = 1;

public:
	void findPotentialMatches( GemScene const & scene );
	void findMatches( GemScene const & scene );
};