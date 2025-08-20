#ifndef	Hex_HPP
#define	Hex_HPP

// includes //

template <typename T>
class Hex
{
	private:
		//====================================== ATTRIBUTES ========//
		#pragma region attributes 

			T									_q;
			T									_r;
			T									_s;

		#pragma endregion attributes
		//==========================================================//

	public:
		//============================= CONST & DESTRUCTORS ========//
		#pragma region constructors

			Hex<T>( T q, T r, T s );
			Hex<T>( T q, T r );
			Hex<T>(const Hex<T>& copy);
			~Hex<T>();

		#pragma endregion attributes
		//==========================================================//

		//========================================= METHODS ========//
		#pragma region methods

			Hex<T>	multiply(const Hex<T>& lhs, int k);

		#pragma endregion methods
		//==========================================================//

		//======================================= OPERATORS ========//
		#pragma region methods

			Hex<T>&	operator = (const Hex<T>& copy);

		#pragma endregion methods
		//==========================================================//

		//========================================= GETTERS ========//
		#pragma region getters 

			const T&			get_q() const;
			const T&			get_r() const;
			const T&			get_s() const;

		#pragma endregion getters
		//==========================================================//

		//========================================= SETTERS ========//
		#pragma region setters

			void				set_q(const T& value);
			void				set_r(const T& value);
			void				set_s(const T& value);

		#pragma endregion setters
		//==========================================================//

};

#endif // Hex_HPP
