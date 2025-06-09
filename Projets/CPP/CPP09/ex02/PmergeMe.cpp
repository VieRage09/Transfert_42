/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:13:02 by tlebon            #+#    #+#             */
/*   Updated: 2025/06/09 18:38:20 by tlebon           ###   ########.fr       */
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

// Creates and loads 2 vectors (main & pend) then insert the pend into main and update _vec in the end
void PmergeMe::insert_vec(unsigned int elem_size)
{
	std::vector<std::pair<int, std::vector<int>>>	main;
	std::vector<std::pair<int, std::vector<int>>>	pend;
	std::vector<int> remains;

	std::vector<std::pair<int, std::vector<int>>>	a_s;
	std::vector<std::pair<int, std::vector<int>>>	b_s;

	std::cout << "insert_vec called with elem_size: " << elem_size << std::endl;
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
	// Garde les elements qui ne participent pas a l'insertion (incapable de former un element complet)
	if (it != _vec.end())
		for (std::vector<int>::iterator it_elem = it; it_elem != _vec.end(); it_elem++)
			remains.push_back(*it_elem);
	main.insert(main.end(), b_s.begin(), b_s.begin() + 1);
	main.insert(main.end(), a_s.begin(), a_s.end());
	pend.insert(pend.end(), b_s.begin() + 1, b_s.end()); // Attention dans le cas ou on ne peux pas faire de pend

	// Affichage des vecteurs a_s, b_s, main et pend
	std::cout << "a_s:\n";
	for (const auto &pair : a_s)
	{
		std::cout << "Index: " << pair.first << " Values: ";
		for (const auto &val : pair.second)
			std::cout << val << " ";
		std::cout << std::endl;
	}
	std::cout << "b_s:\n";
	for (const auto &pair : b_s)
	{
		std::cout << "Index: " << pair.first << " Values: ";
		for (const auto &val : pair.second)
			std::cout << val << " ";
		std::cout << std::endl;
	}
	std::cout << "main:\n";
	for (const auto &pair : main)
	{
		std::cout << "Index: " << pair.first << " Values: ";
		for (const auto &val : pair.second)
			std::cout << val << " ";
		std::cout << std::endl;
	}
	std::cout << "pend:\n";
	for (const auto &pair : pend)
	{
		std::cout << "Index: " << pair.first << " Values: ";
		for (const auto &val : pair.second)
			std::cout << val << " ";
		std::cout << std::endl;
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
		std::cout << "Pas d'insertion pour le moment, pend n'est pas vide" << std::endl;
	}
	for (std::vector<int>::iterator it = remains.begin(); it != remains.end(); it++) // On ajoute en queue les valeurs qui n'ont pas participees a l'insertion
		main.emplace_back(0, *it);
	// _vec.clear();
	// std::cout << "Vec cleared\n";
	// On remet les valeurs de main dans _vec
	// for (std::vector<std::pair<int, std::vector<int>>>::iterator it; it != main.end(); it++)
	// {
	// 	_vec.insert(_vec.end(), (*it).second.begin(), (*it).second.end());
	// }
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
	display_vec();
	insert_vec(pair_size / 2);
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
