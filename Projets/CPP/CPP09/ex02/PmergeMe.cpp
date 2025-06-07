/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:13:02 by tlebon            #+#    #+#             */
/*   Updated: 2025/06/07 17:45:52 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

// Displays the private attribute _vec
void	PmergeMe::display_vec() const
{
	std::cout << "Vector of size " << _vec.size() << ":\n";
	for(auto it = _vec.begin(); it != _vec.end(); it++)
	{
		std::cout << *it << std::endl;
	}
}

// Displays the private attribute _deq
void	PmergeMe::display_deq() const
{
	std::cout << "Deque:\n";
	for(auto it = _deq.begin(); it != _deq.end(); it++)
	{
		std::cout << *it << std::endl;
	}
}

// Used to check if we can increment pos n times w/o getting past end()
template <typename T>
bool	PmergeMe::safe_advance(typename T::iterator pos, unsigned int n) const
{
	int i = 0;
	for (auto it = pos; i < n ; it++, i++)
	{
		if (it == _vec.end())
			return (false);
	}
	return (true);
}

// Sort blocks of numbers following the first step of FJ algo
void	PmergeMe::sort_pairs(unsigned int pair_size)
{
	for (std::vector<int>::iterator it = _vec.begin(); safe_advance<std::vector<int>>(it, pair_size); it += pair_size)
	{
		if (pair_size == 2 && *it > *(it + 1))
			std::iter_swap(it, it + 1);
		else if (pair_size > 2 && *(it + (pair_size / 2) - 1) > *(it + pair_size - 1))
			std::swap_ranges(it, it + (pair_size / 2), it + (pair_size / 2));
	}	
}

// Creates and loads 2 vectors (main & pend) then insert the pend into main and update _vec in the end
void	PmergeMe::insert_vec(unsigned int elem_size)
{
	std::vector<int>	main;
	std::vector<int>	pend;
	std::vector<int>	remains;

	bool				is_upper_in_pair = false;

	std::cout << "insert_vec called with elem_size: " << elem_size << std::endl;
	// Loading main's 2 first elems 
	for (std::vector<int>::iterator it = _vec.begin(); it != _vec.begin() + (elem_size * 2); it++)
		main.push_back(*it);
	for(std::vector<int>::iterator it = _vec.begin() + (elem_size * 2); safe_advance<std::vector<int>>(it, elem_size); it += elem_size)
	{
		if (!is_upper_in_pair)
			for(std::vector<int>::iterator it_elem = it; it_elem != it + elem_size; it_elem++)
				pend.push_back(*it_elem);
		else
			for(std::vector<int>::iterator it_elem = it; it_elem != it + elem_size; it_elem++)
				main.push_back(*it_elem);
		is_upper_in_pair = !is_upper_in_pair;
		if (!safe_advance<std::vector<int>>(it, elem_size)) // Normalement, garde les elements qui ne participent pas a l'insertion (incapable de former un element complet): A TESTER
			for(std::vector<int>::iterator it_elem = it; it_elem != it + elem_size; it_elem++)
				remains.push_back(*it_elem);
	}
	if (!pend.empty()) // Algo d'insertion a faire
	{
		
		// Insert the pend into main
	}
	for(std::vector<int>::iterator it = remains.begin(); it != remains.end(); it++) // On ajoute en queue les valeurs qui n'ont pas participees a l'insertion
		main.push_back(*it);
	_vec.swap(main);
	main.clear(); // Useless je pense
	pend.clear();
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
	display_vec();
	insert_vec(pair_size / 2);
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
