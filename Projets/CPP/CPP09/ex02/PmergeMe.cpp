#include "PmergeMe.hpp"

// CONSTRUCTORS & DESTRUCTORS //

PmergeMe::PmergeMe(bool args, char **list) : _vec(std::vector<int>()), _deq(std::deque<int>())
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
		i = 1;
		while (list[i])
		{
			_vec.push_back(std::stoi(list[i]));
			_deq.push_back(std::stoi(list[i]));
			i++;
		}
	}
	std::cout << "PmergeMe object instanciated\n";
}

PmergeMe::PmergeMe(const PmergeMe& copy) : _vec(std::vector<int>(copy._vec)), _deq(std::deque<int>(copy._deq))
{
	std::cout << "PmergeMe object copied\n";
}

PmergeMe::~PmergeMe() { std::cout << "PmergeMe object destroyed\n";}

// METHODS //

void	PmergeMe::display_containers() const
{
	std::cout << "Vector:\n";
	for(auto it = _vec.begin(); it != _vec.end(); it++)
	{
		std::cout << *it << std::endl;
	}
	std::cout << "Deque:\n";
	for(auto it = _deq.begin(); it != _deq.end(); it++)
	{
		std::cout << *it << std::endl;
	}
}

// OPERATORS //

PmergeMe& PmergeMe::operator = (const PmergeMe& copy)
{
	if (this != &copy)
	{
		_vec = copy._vec;	// Check si ca marche ca
		_deq = copy._deq;
	}
	return (*this);
}

// GETTERS //

const std::vector<int>&	PmergeMe::get_vec() const { return ( _vec );}
const std::deque<int>&	PmergeMe::get_deq() const { return ( _deq );}
