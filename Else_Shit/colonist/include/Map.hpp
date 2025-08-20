#ifndef	MAP_HPP
#define	MAP_HPP

// includes //
#include <colonist.hpp>
#include <vector>
#include <fstream>

class Tile;

class Map
{
	private:
		//====================================== ATTRIBUTES ========//
		#pragma region attributes 

			size_t				map_size;
			std::vector<Tile>	v_map;	

		#pragma endregion attributes
		//==========================================================//

		//========================================= METHODS ========//
		#pragma region pmethods

		#pragma endregion pmethods
		//==========================================================//

	public:
		//============================= CONST & DESTRUCTORS ========//
		#pragma region constructors

			Map( std::string file_path );
			Map(const Map& copy);
			~Map();

		#pragma endregion attributes
		//==========================================================//

		//========================================= METHODS ========//
		#pragma region methods

		#pragma endregion methods
		//==========================================================//

		//======================================= OPERATORS ========//
		#pragma region methods

			Map&	operator = (const Map& copy);

		#pragma endregion methods
		//==========================================================//

};

#endif // MAP_HPP
