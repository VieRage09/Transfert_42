#ifndef	TILE_HPP
#define	TILE_HPP

// includes //
#include <iostream>



// defines //
// Une enum maybe ????
#define DESERT_TILE		10
#define WOOD_TILE		11
#define BRICK_TILE		12
#define SHEEP_TILE		13
#define WHEAT_TILE		14
#define STONE_TILE		15
#define WATER_TILE		16

//////////////////////////

class Tile
{
	private:
		//====================================== ATTRIBUTES ========//
		#pragma region attributes 

			int								map_pos;

			int								type;
			unsigned int					number;
			bool							thief;

			Tile *							noea_tile;
			Tile *							nowe_tile;
			Tile *							ea_tile;
			Tile *							we_tile;
			Tile *							soea_tile;
			Tile *							sowe_tile;

		#pragma endregion attributes
		//==========================================================//

	public:
		//============================= CONST & DESTRUCTORS ========//
		#pragma region constructors

			Tile(int map_pos, int type, unsigned int num);
			~Tile();

		#pragma endregion attributes
		//==========================================================//

		//========================================= METHODS ========//
		#pragma region methods

		#pragma endregion methods
		//==========================================================//

		//======================================= OPERATORS ========//
		#pragma region methods

			Tile&	operator = (const Tile& copy);

		#pragma endregion methods
		//==========================================================//

		//========================================= GETTERS ========//
		#pragma region getters 

			const int &				get_type() const;
			const unsigned int &	get_number() const;
			const bool &			get_thief() const;
			const Tile *			get_noea_tile() const;
			const Tile *			get_nowe_tile() const;
			const Tile *			get_ea_tile() const;
			const Tile *			get_we_tile() const;
			const Tile *			get_soea_tile() const;
			const Tile *			get_sowe_tile() const;

		#pragma endregion getters
		//==========================================================//

		//========================================= SETTERS ========//
		#pragma region setters

			void				set_type(int & value);
			void				set_number(unsigned int & value);
			void				set_thief(bool & value);
			void				set_noea_tile(Tile * value);

		#pragma endregion setters
		//==========================================================//

};

#endif // TILE_HPP
