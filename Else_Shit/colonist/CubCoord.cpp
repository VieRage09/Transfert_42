#include "Hex.hpp"

//============================================================ CONSTRUCTORS & DESTRUCTORS ========//
#pragma region constructors

template <typename T>
Hex<T>::Hex( T q, T r, T s )
{
	if (q + r + s != 0)
		throw std::invalid_argument("Invalid Hex: q + r + s must equal 0");
	_q = q;
	_r = r;
	_s = s;
}

template <typename T>
Hex<T>::Hex( T q, T r )
{
	_q = q;
	_r = r;
	_s = - (q + r);
}

template <typename T>
Hex<T>::Hex(const Hex<T>& copy) : _q(copy._q), _r(copy._r), _s(copy._s) {}

template <typename T>
Hex<T>::~Hex() {}


#pragma endregion constructors
//================================================================================================//


//=============================================================================== METHODS ========//
#pragma region methods



// Arithmetics
template <typename T>
Hex<T>	Hex<T>::multiply(const Hex<T> & hex, int k)
{
	return Hex<T>(
		hex.get_q() * k,
		hex.get_r() * k,
		hex.get_s() * k
	);
}

#pragma endregion methods
//================================================================================================//


//============================================================================= OPERATORS ========//
#pragma region operators

template <typename T>
Hex<T>& Hex<T>::operator = (const Hex<T>& copy)
{
	if (this != &copy)
	{
		_q = copy._q;
		_r = copy._r;
		_s = copy._s;
	}
	return (*this);
}

template <typename T>
bool operator == (const Hex<T>& lhs, const Hex<T>& rhs) { return (lhs._q == rhs._q && lhs._r == rhs._r && lhs._s == rhs._s); }

template <typename T>
bool operator != (const Hex<T>& lhs, const Hex<T>& rhs) { return !(lhs == rhs); }

template <typename T>
Hex<T> operator + (const Hex<T>& lhs, const Hex<T>& rhs) { return Hex<T>(lhs._q + rhs._q, lhs._r + rhs._r, lhs._s + rhs._s); }

template <typename T>
Hex<T> operator - (const Hex<T>& lhs, const Hex<T>& rhs) { return Hex<T>(lhs._q - rhs._q, lhs._r - rhs._r, lhs._s - rhs._s); }

#pragma endregion operators
//================================================================================================//


//=============================================================================== GETTERS ========//
#pragma region getters

template <typename T>
const T&	Hex<T>::get_q() const { return ( _q );}
template <typename T>
const T&	Hex<T>::get_r() const { return ( _r );}
template <typename T>
const T&	Hex<T>::get_s() const { return ( _s );}

#pragma endregion getters
//================================================================================================//


//=============================================================================== SETTERS ========//
#pragma region setters

template <typename T>
void	Hex<T>::set_q(const T& value) { _q = value; }
template <typename T>
void	Hex<T>::set_r(const T& value) { _r = value; }
template <typename T>
void	Hex<T>::set_s(const T& value) { _s = value; }

#pragma endregion setters
//================================================================================================//

