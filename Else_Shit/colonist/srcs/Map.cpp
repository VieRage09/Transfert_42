#include "Map.hpp"

//============================================================ CONSTRUCTORS & DESTRUCTORS ========//
#pragma region constructors

// A proteger
Map::Map( std::string file_path ) : map_size(7)
{
	
}

Map::Map(const Map& copy) {}

Map::~Map() {}


#pragma endregion constructors
//================================================================================================//

//======================================================================= PRIVATE METHODS ========//
#pragma region pmethods


#pragma endregion pmethods
//================================================================================================//

//=============================================================================== METHODS ========//
#pragma region methods


#pragma endregion methods
//================================================================================================//


//============================================================================= OPERATORS ========//
#pragma region operators

Map& Map::operator = (const Map& copy)
{
	if (this != &copy)
	{

	}
	return (*this);
}

#pragma endregion operators
//================================================================================================//

