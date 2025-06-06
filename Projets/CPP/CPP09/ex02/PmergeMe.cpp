#include "PmergeMe.hpp"

//############################## CONSTRUCTORS & DESTRUCTORS #####################################//

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

//############################### METHODS #######################################################//


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
	for (std::vector<int>::iterator it = _vec.begin(); safe_advance(it, pair_size); it += pair_size)
	{
		if (pair_size == 2 && *it > *(it + 1))
		{
			// std::cout << "Swapping: " << *it << " and " << *(it + 1) << std::endl;
			std::iter_swap(it, it + 1);
		}
		else if (pair_size > 2 && *(it + (pair_size / 2) - 1) > *(it + pair_size - 1))
		{
			// std::cout << "Swapping pair: [" << *(it + (pair_size / 2) - 1) << ", " << *(it + (pair_size - 1)) << "]" << std::endl;
			std::swap_ranges(it, it + (pair_size / 2), it + (pair_size / 2));
		}
		// else
		// 	std::cout << "No swap needed for pair [" << *(it + (pair_size / 2) - 1) << ", " << *(it + pair_size - 1) << "]" << std::endl;
	}	
}

// Used by sort_vector to recursively create/sort pairs and call other functions for main pend etc
void	PmergeMe::recursive_sort(unsigned int pair_size)
{
	std::cout << "Recursive sort called with pair size: " << pair_size << std::endl;
	sort_pairs(pair_size);
	// std::cout << "Displaying vector sorted with pair size = " << pair_size << std::endl;
	// display_vec();	
	if (pair_size <= _size / 2)
		recursive_sort(pair_size * 2);
	
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

//############################## OPERATORS ######################################################//

PmergeMe& PmergeMe::operator = (const PmergeMe& copy)
{
	if (this != &copy)
	{
		_vec = copy._vec;	// Check si ca marche ca
		_deq = copy._deq;
	}
	return (*this);
}

//############################## GETTERS ########################################################//

const std::vector<int>&	PmergeMe::get_vec() const { return ( _vec );}
const std::deque<int>&	PmergeMe::get_deq() const { return ( _deq );}
