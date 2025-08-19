#include "Map.hpp"

//============================================================ CONSTRUCTORS & DESTRUCTORS ========//
#pragma region constructors

// A proteger
Map::Map( std::string file_path ) : map_size(7)
{
	std::ifstream	map_stm(file_path);
	std::string buff;
	std::string value;
	int			map_pos = 0;

	while (std::getline(map_stm, buff))
	{
		int next_pos = buff.find_first_not_of(" \t");
		while (next_pos != std::string::npos)
		{
			buff = buff.substr(next_pos);
			value = buff.substr(0, 3);
			int type = str_to_type(value);
			if (type == -1)
				throw std::runtime_error("Invalid type in map");
			Tile	tmp(map_pos, type, map_pos + 2);
			v_map.push_back(tmp);
			buff = buff.substr(3);
			next_pos = buff.find_first_not_of(" \t");
			map_pos++;
		}
	}
}

Map::Map(const Map& copy) {}

Map::~Map() {}


#pragma endregion constructors
//================================================================================================//

//======================================================================= PRIVATE METHODS ========//
#pragma region pmethods

int	Map::str_to_type(std::string abrev)
{
	if (abrev.compare("DES") == 0)
		return (DESERT_TILE);
	if (abrev.compare("WOO") == 0)
		return (WOOD_TILE);
	if (abrev.compare("BRI") == 0)
		return (BRICK_TILE);
	if (abrev.compare("SHE") == 0)
		return (SHEEP_TILE);
	if (abrev.compare("WHE") == 0)
		return (WHEAT_TILE);
	if (abrev.compare("STO") == 0)
		return (STONE_TILE);
	return (-1);
}

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

