#pragma once
#include <string>
class Asset
{
	std::string _ID;
public:
	Asset( std::string ID ) : _ID( ID ) {}
	virtual ~Asset() = default;
	std::string const & getID() const { return _ID; }
};
