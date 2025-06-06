#include "PmergeMe.hpp"

//############################## CONSTRUCTORS & DESTRUCTORS #####################################//

//------------------------------ PMERGEME -------------------------------------------------------//
PmergeMe::PmergeMe(bool args, char **list)
: _vec(std::vector<int>()), _deq(std::deque<int>())
{
	int	i;
	if (args)
	{
		std::string	str = list[1];
		i = 0;
		while (str[i])
		{
			// A voir si je gere vraiment le cas ./PmergeMe "1 2 3 4"
			i++;
		}
	}
	else
	{
		_size = 0;
		i = 1;
		while (list[i])
		{
			_vec.push_back(std::stoi(list[i]));
			_deq.push_back(std::stoi(list[i]));
			_size++;
			i++;
		}
	}
	std::cout << "PmergeMe object instanciated\n";
}

PmergeMe::PmergeMe(const PmergeMe& copy)
: _vec(std::vector<int>(copy._vec)), _deq(std::deque<int>(copy._deq))
{
	std::cout << "PmergeMe object copied\n";
}

PmergeMe::~PmergeMe() { std::cout << "PmergeMe object destroyed\n";}
//-----------------------------------------------------------------------------------------------//

//------------------------------ PAIR -----------------------------------------------------------//
template <typename T>
PmergeMe::Pair<T>::Pair(typename T::const_iterator start, typename T::const_iterator finish)
: _start(start), _finish(finish) {}

template <typename T>
PmergeMe::Pair<T>::Pair(const Pair<T> & copy) : _start(copy._start), _finish(copy._finish) {}

template <typename T>
PmergeMe::Pair<T>::~Pair() {}
//-----------------------------------------------------------------------------------------------//

//############################### METHODS #######################################################//

//------------------------------ PMERGEME -------------------------------------------------------//

// Public Methods // 

void	PmergeMe::display_vec() const
{
	std::cout << "Vector of size " << _vec.size() << ":\n";
	for(auto it = _vec.begin(); it != _vec.end(); it++)
	{
		std::cout << *it << std::endl;
	}
}

void	PmergeMe::display_deq() const
{
	std::cout << "Deque:\n";
	for(auto it = _deq.begin(); it != _deq.end(); it++)
	{
		std::cout << *it << std::endl;
	}
}

// Idee d'implementation pour la phase 1 (n nombres a trier):
// Ordre 1: chaque element contient un seul nombre. --> On peut trier deux a deux directement dans _vec ou dans un copie exclusive a la fonction recursive ?
// Ordre 2: chaque element contient une paire de nombre. --> Vecteur de vecteur: Les sous vecteurs contiennent une paire de nombre (.top() pour recup le nombre a droite), puis on switch
// Ordre 3: chaque element contient une paire de paire de nombre (4). --> Vecteur de vecteur de vecteur

bool	PmergeMe::safe_advance(std::vector<int>::iterator pos, unsigned int n) const
{
	int i = 0;
	for (std::vector<int>::iterator it = pos; i < n ; it++, i++)
	{
		if (it == _vec.end())
			return (false);
	}
	return (true);
}

// Sort pairs of numbers or pairs of pairs etc following the the first step of FJ algo
void	PmergeMe::sort_pairs(unsigned int pair_size)
{
	for (std::vector<int>::iterator it = _vec.begin(); safe_advance(it, pair_size); it += pair_size) // Check si ca marche pour odd --> Shift fonctiona recoder
	{
		if (pair_size == 2 && it != _vec.end() - 1 && *it > *(it + 1))
		{
			std::cout << "Swapping: " << *it << " and " << *(it + 1) << std::endl;
			std::iter_swap(it, it + 1); // PB: Ne swap pas les nombre par chunck mais 1 a 1
		}
		else if (pair_size > 2 && it != _vec.end() - pair_size + 1 && *(it + (pair_size / 2) - 1) > *(it + pair_size - 1))
		{
			std::cout << "Swapping pair: [" << *it << ", " << *(it + (pair_size - 1)) << "]" << std::endl;
			std::swap_ranges(it, it + (pair_size / 2), it + (pair_size / 2));
		}
		else
			std::cout << "No swap needed for pair [" << *it << ", " << *(it + pair_size - 1) << "]" << std::endl;
	}	
}

// Used by sort_vector to recursively create/sort pairs and call other functions for main pend etc
void	PmergeMe::recursive_sort(unsigned int pair_size)
{
	std::cout << "Recursive sort called with pair size: " << pair_size << std::endl;
	sort_pairs(pair_size);
	std::cout << "Displaying vector sorted with pair size = " << pair_size << std::endl;
	display_vec();	
	if (pair_size <= _size / 2)
		recursive_sort(pair_size * 2);
	else
		return ;// Suite de l'algo main pend tout ca
}


// Sort _vec following Ford-Johnson algo
void	PmergeMe::sort_vector()
{
	recursive_sort(2);
}

void	PmergeMe::sort_deque()
{

}
//-----------------------------------------------------------------------------------------------//

//------------------------------ PAIR -----------------------------------------------------------//

template <typename T>
void	PmergeMe::Pair<T>::sort_pair()
{
	size_t 						range = std::distance(_start, _finish);
	typename T::const_iterator	left = _start + range / 2 - 1;
	typename T::const_iterator	right = _finish;

	if (*left > *right)
	
		// Operate swap
	return ;
}
//-----------------------------------------------------------------------------------------------//

//############################## OPERATORS ######################################################//

//------------------------------ PMERGEME -------------------------------------------------------//

PmergeMe& PmergeMe::operator = (const PmergeMe& copy)
{
	if (this != &copy)
	{
		_vec = copy._vec;	// Check si ca marche ca
		_deq = copy._deq;
	}
	return (*this);
}
//-----------------------------------------------------------------------------------------------//

//------------------------------ PAIR -----------------------------------------------------------//

template <typename T>
PmergeMe::Pair<T>&		PmergeMe::Pair<T>::operator = (const PmergeMe::Pair<T>& copy)
{
	if (this != &copy)
	{
		_start = copy._start;
		_finish = copy._finish;
	}
	return (*this);
}

template <typename T>
std::ostream&	operator << (std::ostream & os, const PmergeMe::Pair<T>& pair)
{
	os << "Pair: ";
	for(auto it = pair.get_start(); it != pair.get_finish() + 1; it++) // ATTENTION: Surement bancal le get_finish() + 1 
		os << *it << " ";
	return (os);
}
//-----------------------------------------------------------------------------------------------//

//############################## GETTERS ########################################################//

//------------------------------ PMERGEME -------------------------------------------------------//
const std::vector<int>&	PmergeMe::get_vec() const { return ( _vec );}
const std::deque<int>&	PmergeMe::get_deq() const { return ( _deq );}
//-----------------------------------------------------------------------------------------------//

//------------------------------ PAIR -----------------------------------------------------------//

template <typename T>
const typename T::const_iterator & PmergeMe::Pair<T>::get_start() const { return (_start); }
template <typename T>
const typename T::const_iterator & PmergeMe::Pair<T>::get_finish() const { return (_finish); }
//-----------------------------------------------------------------------------------------------//