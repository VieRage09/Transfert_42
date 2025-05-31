#include "PmergeMe.hpp"

// CONSTRUCTORS & DESTRUCTORS //

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

// METHODS //

//------------------------------ PMERGEME -------------------------------------------------------//

// Private methods //
void	PmergeMe::create_pairs(std::vector<Pair<std::vector<int>>> & tab, unsigned int pair_size)
{
	for (auto it = _vec.begin(); it != _vec.end(); it += pair_size)
	{
		if (it + pair_size - 1 != _vec.end()) // Voir si ca marche si on depasse carrement end()
			tab.push_back(Pair<std::vector<int>>(it, it + pair_size - 1));
		else
			return ;
	}
}

// Public Methods // 

void	PmergeMe::display_vec() const
{
	std::cout << "Vector:\n";
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

// Algo =
// 1. Former des pair d'elements (pair de nombre au depart, puis pair de pair de nombre etc)
// 2. Trier dans l'ordre ces pairs (ascendant, on trie les pairs de pair de nombre en checkant le nombre le plus gros de chaque)
// --> 

void	PmergeMe::recursive_sort(unsigned int pair_size)
{
	std::vector<Pair<std::vector<int>>> pair_vec;

	create_pairs(pair_vec, pair_size);
	for(auto elem : pair_vec)
		elem.sort_pair();
	if (pair_size <= _size)
		recursive_sort(pair_size * 2);
	// else
		// Suite de l'algo main pend tout ca
}


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
	
}
//-----------------------------------------------------------------------------------------------//

// OPERATORS //

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

// GETTERS //

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