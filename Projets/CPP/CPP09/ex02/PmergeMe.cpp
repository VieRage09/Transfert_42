/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:13:02 by tlebon            #+#    #+#             */
/*   Updated: 2025/06/10 13:19:39by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

// ############################## CONSTRUCTORS & DESTRUCTORS #####################################//

PmergeMe::PmergeMe(char **list)
	: _vec(std::vector<int>()), _deq(std::deque<int>())
{
	int i;

	_size = 0;
	i = 1;
	while (list[i])
	{
		_vec.push_back(std::stoi(list[i]));
		_deq.push_back(std::stoi(list[i]));
		_size++;
		i++;
	}
	std::cout << "PmergeMe object instanciated\n";
}

PmergeMe::PmergeMe(const PmergeMe &copy)
	: _vec(std::vector<int>(copy._vec)), _deq(std::deque<int>(copy._deq))
{
	std::cout << "PmergeMe object copied\n";
}

PmergeMe::~PmergeMe() { std::cout << "PmergeMe object destroyed\n"; }

// ############################### METHODS #######################################################//

// PRIVATE METHODS //

// Used to check if we can increment pos n times w/o getting past end()
template <typename T>
bool PmergeMe::safe_advance(typename T::iterator pos, unsigned int n) const
{
	int i = 0;
	for (auto it = pos; i < n; it++, i++)
	{
		if (it == _vec.end())
			return (false);
	}
	return (true);
}

// Sort blocks of numbers following the first step of FJ algo
void PmergeMe::sort_pairs(unsigned int pair_size)
{
	for (std::vector<int>::iterator it = _vec.begin(); safe_advance<std::vector<int>>(it, pair_size); it += pair_size)
	{
		if (pair_size == 2 && *it > *(it + 1))
			std::iter_swap(it, it + 1);
		else if (pair_size > 2 && *(it + (pair_size / 2) - 1) > *(it + pair_size - 1))
			std::swap_ranges(it, it + (pair_size / 2), it + (pair_size / 2));
	}
}

unsigned int	PmergeMe::get_nth_jacobsthal(unsigned int n) const
{
	if (n == 0)
		return (0);
	if (n == 1)
		return (1);
	return (static_cast<unsigned int>(round(pow(2, n) - pow(-1, n)) / 3));
}

// int binarySearch(int a[], int item,
//                 int low, int high)
// {
//     if (high <= low)
//         return (item > a[low]) ?
//                 (low + 1) : low;

//     int mid = (low + high) / 2;

//     if (item == a[mid])
//         return mid + 1;

//     if (item > a[mid])
//         return binarySearch(a, item,
//                             mid + 1, high);
//     return binarySearch(a, item, low,
//                         mid - 1);
// }


std::vector<std::pair<int, std::vector<int>>>::iterator	binary_search(
	std::vector<std::pair<int, std::vector<int>>> &main,
	std::pair<int, std::vector<int>> &elem,
	std::vector<std::pair<int, std::vector<int>>>::iterator lower_bound,
	std::vector<std::pair<int, std::vector<int>>>::iterator upper_bound)
{
	if ((*upper_bound).second.back() <= (*lower_bound).second.back()) // Pas forcement une belle implementation
		return (elem.second.back() > (*lower_bound).second.back()) ? lower_bound + 1 : lower_bound;

	std::vector<std::pair<int, std::vector<int>>>::iterator mid = lower_bound + std::distance(lower_bound, upper_bound) / 2;

	if (elem.second.back() == (*mid).second.back())
		return mid + 1;

	if (elem.second.back() > (*mid).second.back())
		return binary_search(main, elem, mid + 1, upper_bound);

	return binary_search(main, elem, lower_bound, mid - 1);
}

void	PmergeMe::binary_insert(std::pair<int, std::vector<int>> &elem,
	std::vector<std::pair<int, std::vector<int>>> &main) const
{
	std::vector<std::pair<int, std::vector<int>>>::iterator	insert_pos;
	std::vector<std::pair<int, std::vector<int>>>::iterator	upper_bound = main.begin();

	for(; upper_bound != main.end(); upper_bound++)
		if ((*upper_bound).first == elem.first)
			break;
	if (upper_bound == main.end())
	{
		upper_bound--;
		std::cout << "Upper bound not found, using last element" << std::endl;
	}
	//print upper_bound vector
	for(std::vector<int>::iterator it = (*upper_bound).second.begin(); it != (*upper_bound).second.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;

	insert_pos = binary_search(main, elem, main.begin(), upper_bound);
	main.insert(insert_pos, elem);
}

void	PmergeMe::insert_pend(std::vector<std::pair<int, std::vector<int>>> &main,
	std::vector<std::pair<int, std::vector<int>>> &pend,
	std::vector<std::pair<int, std::vector<int>>> &a_s) const
{
	int				n = 3;
	unsigned int	jacobsthal = get_nth_jacobsthal(n);
	while (!pend.empty())
	{
		if (pend.back().first < jacobsthal)
		{
			// Prints
			std::cout << "Inserting last pend element: " << "index = " << pend.back().first << std::endl;
			for (std::vector<int>::iterator it = pend.back().second.begin(); it != pend.back().second.end(); it++)
				std::cout << *it << " ";
			std::cout << std::endl;
			// 
			binary_insert(pend.back(), main);
			pend.erase(pend.end() - 1); // Erase l'element insere
			continue;
		}
		for (std::vector<std::pair<int, std::vector<int>>>::reverse_iterator rit = pend.rend() - jacobsthal + 1; rit != pend.rend(); ++rit)
		{
			// Prints
			std::cout << "Inserting pend element: " << "index = " << (*rit).first << std::endl;
			for (std::vector<int>::iterator it = (*rit).second.begin(); it != (*rit).second.end(); it++)
				std::cout << *it << " ";
			std::cout << std::endl;
			//
			binary_insert(*rit, main);
		}
		pend.erase(pend.begin(), pend.begin() + jacobsthal - get_nth_jacobsthal(n - 1) - 1);
		jacobsthal = get_nth_jacobsthal(++n);
		// prints
		std::cout << "New jacobsthal number: " << jacobsthal << std::endl;
		std::cout << "Main vector after insertion:\n";
		for (auto &pair : main)
		{
			std::cout << "Index: " << pair.first << " Elements: ";
			for (auto &elem : pair.second)
				std::cout << elem << " ";
			std::cout << std::endl;
		}
		if (pend.empty())
			break;
		std::cout << "Pend vector after insertion:\n";
		for (auto &pair : pend)
		{
			std::cout << "Index: " << pair.first << " Elements: ";
			for (auto &elem : pair.second)
				std::cout << elem << " ";
			std::cout << std::endl;
		}
		//
	}
}

// Creates and loads 2 vectors (main & pend) then insert the pend into main and update _vec in the end
void	PmergeMe::insert_vec(unsigned int elem_size)
{
	std::vector<std::pair<int, std::vector<int>>>	a_s;
	std::vector<std::pair<int, std::vector<int>>>	b_s;
	std::vector<std::pair<int, std::vector<int>>>	main;
	std::vector<std::pair<int, std::vector<int>>>	pend;
	std::vector<int>								remains;

	std::cout << "Inserting vector with element size: " << elem_size << std::endl;
	bool	is_biggest_in_pair = false;
	int		index = 1;
	// Loading a_s and b_s so we can keep for later their labels
	std::vector<int>::iterator it = _vec.begin();
	for (; safe_advance<std::vector<int>>(it, elem_size); it += elem_size)
	{
		if (!is_biggest_in_pair)
			b_s.emplace_back(index, std::vector<int>(it, it + elem_size));
		else
			a_s.emplace_back(index, std::vector<int>(it, it + elem_size));
		if (is_biggest_in_pair)
			index++;
		is_biggest_in_pair = !is_biggest_in_pair;
	}
	// Keep the elements that do not participate for this round
	if (it != _vec.end())
		for (std::vector<int>::iterator it_elem = it; it_elem != _vec.end(); it_elem++)
			remains.push_back(*it_elem);
	// Creating main and pend
	main.insert(main.end(), b_s.begin(), b_s.begin() + 1);
	main.insert(main.end(), a_s.begin(), a_s.end());
	pend.insert(pend.end(), b_s.begin() + 1, b_s.end()); // Attention dans le cas ou on ne peux pas faire de pend

	std::cout << "Vectors after loading:\n";
	// Display vectors for debug
	std::cout << "a_s vector:\n";
	for (auto &pair : a_s)
	{
		std::cout << "Index: " << pair.first << " Elements: ";
		for (auto &elem : pair.second)
			std::cout << elem << " ";
		std::cout << std::endl;
	}
	std::cout << "b_s vector:\n";
	for (auto &pair : b_s)
	{
		std::cout << "Index: " << pair.first << " Elements: ";
		for (auto &elem : pair.second)
			std::cout << elem << " ";
		std::cout << std::endl;
	}
	std::cout << "main vector:\n";
	for (auto &pair : main)
	{
		std::cout << "Index: " << pair.first << " Elements: ";
		for (auto &elem : pair.second)
			std::cout << elem << " ";
		std::cout << std::endl;
	}
	std::cout << "pend vector:\n";
	for (auto &pair : pend)
	{
		std::cout << "Index: " << pair.first << " Elements: ";
		for (auto &elem : pair.second)
			std::cout << elem << " ";
		std::cout << std::endl;
	}	
	std::cout << "remains vector:\n";
	for (auto &elem : remains)
	{
		std::cout << elem << " ";
	}
	std::cout << std::endl;

	// A partir de la, il faut inserer pend dans main
	// Algo d'insertion binaire = '
	// 0. Calculer le jackobstal number --> Nous dis quel element doit etre insere en premier dans main
	// --> si jakob > au nbr d'elements dans b on insert du dernier au premier restants
	// --> Faire en sorte de supprimer les b deja integres
	// 1. Definir upperbound pour l'element --> Suffit de se referrer a l'index pour trouver le jumeau dans main
	// 2. Binary insertion sort sur la plage etablie dans le main
	// 3. Si on a insere assez d'elements, il faut recalculer le jackobstal number --> back to 0

	if (!pend.empty()) // Algo d'insertion a faire
	{
		std::cout << "Inserting pend into main\n";
		insert_pend(main, pend, a_s);
	}
	// Mettre a jour _vec avec main
	_vec.clear();
	for (std::vector<std::pair<int, std::vector<int>>>::iterator it = main.begin(); it != main.end(); it++)
	{
			_vec.insert(_vec.end(), (*it).second.begin(), (*it).second.end());
	}
	// Adding the remains to _vec 
	_vec.insert(_vec.end(), remains.begin(), remains.end());
	std::cout << "Vector updated with main and remains\n";
	if (_vec.size() != _size)
	{
		std::cerr << "Error: _vec size mismatch after insertion. Expected: " << _size << ", Actual: " << _vec.size() << std::endl;
		exit(EXIT_FAILURE);
	}
	display_vec();
	return ;
}

// Used by sort_vector to recursively create/sort pairs and call other functions for main pend etc
void PmergeMe::recursive_sort(unsigned int pair_size)
{
	std::cout << "Recursive sort called with pair size: " << pair_size << std::endl;
	sort_pairs(pair_size);
	// std::cout << "Displaying vector sorted with pair size = " << pair_size << std::endl;
	// display_vec();
	if (pair_size <= _size / 2)
		recursive_sort(pair_size * 2);
	std::cout << "Displaying vector after recursive sort with pair size = " << pair_size << std::endl;
	display_vec();
	insert_vec(pair_size / 2);
}

// Public Methods //

// Displays the private attribute _vec
void PmergeMe::display_vec() const
{
	std::cout << "Vector of size " << _vec.size() << ":\n";
	for (auto it = _vec.begin(); it != _vec.end(); it++)
	{
		std::cout << *it << std::endl;
	}
}

// Displays the private attribute _deq
void PmergeMe::display_deq() const
{
	std::cout << "Deque:\n";
	for (auto it = _deq.begin(); it != _deq.end(); it++)
	{
		std::cout << *it << std::endl;
	}
}

// Sort _vec following Ford-Johnson algo
void PmergeMe::sort_vector()
{
	recursive_sort(2);
}

void PmergeMe::sort_deque()
{
}

// ############################## OPERATORS ######################################################//

PmergeMe &PmergeMe::operator=(const PmergeMe &copy)
{
	if (this != &copy)
	{
		_vec = copy._vec; // Check si ca marche ca
		_deq = copy._deq;
	}
	return (*this);
}

// ############################## GETTERS ########################################################//

const std::vector<int> &PmergeMe::get_vec() const { return (_vec); }
const std::deque<int> &PmergeMe::get_deq() const { return (_deq); }
