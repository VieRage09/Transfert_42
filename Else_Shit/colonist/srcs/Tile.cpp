#include "Tile.hpp"

//============================================================ CONSTRUCTORS & DESTRUCTORS ========//
#pragma region constructors

Tile::Tile(int map_pos, int type, unsigned int num) : map_pos(map_pos), thief(false)
{
	if (map_pos < 0 || type < DESERT_TILE || type > WATER_TILE || num < 2 || num > 12)
		throw std::runtime_error("Wrong value for tile creation");
	type = type;
	number = num;
	noea_tile = NULL;
	nowe_tile = NULL;
	ea_tile = NULL;
	we_tile = NULL;
	soea_tile = NULL;
	sowe_tile = NULL;
	std::cout	<< "Tile created:\n\t- map_pos = " << map_pos
				<< "\n\t- type = " << type
				<< "\n\t- num = " << num << std::endl;
}

Tile::~Tile() {}


#pragma endregion constructors
//================================================================================================//


//=============================================================================== METHODS ========//
#pragma region methods


#pragma endregion methods
//================================================================================================//


//============================================================================= OPERATORS ========//
#pragma region operators

Tile& Tile::operator = (const Tile& copy)
{
	if (this != &copy)
	{

	}
	return (*this);
}

#pragma endregion operators
//================================================================================================//


//=============================================================================== GETTERS ========//
#pragma region getters

const int &				Tile::get_type() const { return ( type );}
const unsigned int &	Tile::get_number() const { return ( number );}
const bool &			Tile::get_thief() const { return ( thief );}
const Tile *			Tile::get_noea_tile() const { return ( noea_tile );}

#pragma endregion getters
//================================================================================================//


//=============================================================================== SETTERS ========//
#pragma region setters

void	Tile::set_type(int & value) { this->type = value; }
void	Tile::set_number(unsigned int & value) { this->number = value; }
void	Tile::set_thief(bool & value) { this->thief = value; }
void	Tile::set_noea_tile(Tile * value) { this->noea_tile = value; }

#pragma endregion setters
//================================================================================================//

