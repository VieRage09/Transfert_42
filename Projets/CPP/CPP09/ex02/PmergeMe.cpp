/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:13:02 by tlebon            #+#    #+#             */
/*   Updated: 2025/06/25 19:38:38 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

// ############################## CONSTRUCTORS & DESTRUCTORS ################ //
#pragma region construtors
PmergeMe::PmergeMe(char **list)
	: _vec(std::vector<int>()), _deq(std::deque<int>())
{
	int i = 1;

	_size = 0;
	while (list[i])
	{
		_vec.push_back(std::stoi(list[i]));
		_deq.push_back(std::stoi(list[i]));
		_size++;
		i++;
	}
	_nb_comps = 0;
	_max_nb_comps = get_max_nb_comps(_size);
	std::cout << "PmergeMe object instanciated\n";
}

PmergeMe::PmergeMe(const PmergeMe &copy)
	: _vec(std::vector<int>(copy._vec)), _deq(std::deque<int>(copy._deq))
{
	_nb_comps = copy._nb_comps;
	_max_nb_comps = copy._max_nb_comps;
	_size = copy._size;
	std::cout << "PmergeMe object copied\n";
}

PmergeMe::~PmergeMe() { std::cout << "PmergeMe object destroyed\n"; }
#pragma endregion constructors
// ############################## METHODS ################################### //

// ------------------------------ PRIVATE METHODS --------------------------- //
#pragma region private_methods

// Used to check if we can increment pos n times w/o getting past end()
template <typename T>
bool	PmergeMe::safe_advance(typename T::iterator pos, typename T::iterator end, unsigned int n) const
{
	int i = 0;
	for (auto it = pos; i < n; it++, i++)
	{
		if (it == end)
			return (false);
	}
	return (true);
}

// Sort blocks of numbers following the first step of FJ algo
template <typename T>
void	PmergeMe::sort_pairs(T & container, unsigned int pair_size)
{
	for (typename T::iterator it = container.begin(); safe_advance<T>(it, container.end(), pair_size); it += pair_size)
	{
		if (pair_size == 2)
		{
			incr_nb_comps();
			if (*it > *(it + 1))
				std::iter_swap(it, it + 1);
		}
		else if (pair_size > 2)
		{
			incr_nb_comps();
			if (*(it + (pair_size / 2) - 1) > *(it + pair_size - 1))
				std::swap_ranges(it, it + (pair_size / 2), it + (pair_size / 2));
		}
	}
}

void	PmergeMe::load_utils_containers(unsigned int elem_size, Vec_pair & main, Vec_pair &pend, std::vector<int> & remains)
{
	std::vector<int>			first_b(_vec.begin(), _vec.begin() + elem_size);
	std::vector<int>			first_a(_vec.begin() + elem_size, _vec.begin() + 2 * elem_size);

	if (first_b.empty() || first_a.empty())
	{
		std::cerr << "[ERROR] empty elements loaded in main\n";
		exit(EXIT_FAILURE);
	}
	main.emplace_back(1, first_b);
	main.emplace_back(1, first_a);

	std::vector<int>::iterator	it = _vec.begin() + 2 * elem_size;
	bool 						is_biggest_in_pair = false;
	int 						index = 2;

	if (it == _vec.end())
		return ;
	for (; safe_advance<std::vector<int>>(it, _vec.end(), elem_size); it += elem_size)
	{
		std::vector<int> group(it, it + elem_size);
		if (group.empty())
			continue;
		if (!is_biggest_in_pair)
			pend.emplace_back(index, group);
		else
			main.emplace_back(index, group);
		if (is_biggest_in_pair)
			index++;
		is_biggest_in_pair = !is_biggest_in_pair;
	}
	// Keep the elements that do not participate for this round
	if (it != _vec.end())
		for (auto it_elem = it; it_elem != _vec.end(); it_elem++)
			remains.push_back(*it_elem);
}

// Uses binary search to find the position to insert the element in the main vector
Vec_pair::iterator PmergeMe::binary_search(Vec_pair &main,
									const std::pair<int, std::vector<int>> &elem,
									Vec_pair::iterator lower_bound,
									Vec_pair::iterator upper_bound)
{
	int value = elem.second.back();
	auto first = lower_bound;
	auto last = upper_bound;

	while (first < last)
	{
		auto mid = first + (last - first) / 2;
		int mid_value = mid->second.back();
		incr_nb_comps();
		if (value > mid_value)
			first = mid + 1;
		else
			last = mid;
	}
	return first;
}

void PmergeMe::binary_insert(std::pair<int, std::vector<int>> &elem, Vec_pair &main)
{
	Vec_pair::iterator insert_pos;
	Vec_pair::iterator upper_bound = main.begin();

	if (elem.second.empty())
	{
		std::cerr	<< "Error: trying to insert an empty element (index = "
					<< elem.first << ") in binary_insert" << std::endl;
		return;
	}
	for (; upper_bound != main.end(); upper_bound++)
		if ((*upper_bound).first == elem.first)
			break;
	if (upper_bound == main.end())
	{
		if (main.empty())
		{
			std::cerr << "Error: main is empty in binary_insert" << std::endl;
			return;
		}
		if (main.size() == 1)
			upper_bound = main.begin();
		else
		{
			if (upper_bound == main.begin())
				upper_bound = main.begin();
			else
				upper_bound--;
		}
		std::cout << "Upper bound not found, using last element" << std::endl;
	}
	std::cout << "Upper bound found: index = " << (*upper_bound).first << std::endl;
	insert_pos = binary_search(main, elem, main.begin(), upper_bound);
	main.insert(insert_pos, elem);
}

void PmergeMe::insert_pend(Vec_pair &main, Vec_pair &pend)
{
	int n = 3;
	unsigned int jacobsthal = get_nth_jacobsthal(n);

	while (!pend.empty())
	{
		unsigned int prev_jacob = get_nth_jacobsthal(n - 1);
		unsigned int count = jacobsthal - prev_jacob;

		if (count > pend.size())
			count = pend.size();
		for (int i = count - 1; i >= 0; --i)
		{
			std::cout << "Inserting pend element: index = " << pend[i].first << std::endl;
			std::cout << "Elements: ";
			for (std::vector<int>::iterator it = pend[i].second.begin(); it != pend[i].second.end(); ++it)
				std::cout << *it << " ";
			std::cout << std::endl;
			binary_insert(pend[i], main);
		}
		pend.erase(pend.begin(), pend.begin() + count);
		jacobsthal = get_nth_jacobsthal(++n);
	}
}

// Creates and loads 2 vectors (main & pend) then insert the pend into main and update _vec in the end
void PmergeMe::insert_vec(unsigned int elem_size)
{
	Vec_pair main;
	Vec_pair pend;
	std::vector<int> remains;

	load_utils_containers(elem_size, main, pend, remains);

	// display the loaded vectors
	std::cout << "Main vector loaded with " << main.size() << " elements:\n";
	for (auto it = main.begin(); it != main.end(); it++)
	{
		std::cout << "Index: " << it->first << ", Elements: ";
		for (const auto &elem : it->second)
			std::cout << elem << " ";
		std::cout << std::endl;
	}
	std::cout << "Pend vector loaded with " << pend.size() << " elements:\n";
	for (auto it = pend.begin(); it != pend.end(); it++)
	{
		std::cout << "Index: " << it->first << ", Elements: ";
		for (const auto &elem : it->second)
			std::cout << elem << " ";
		std::cout << std::endl;
	}
	std::cout << "Remains vector loaded with " << remains.size() << " elements:\n";
	for (const auto &elem : remains)
	{
		std::cout << elem << " ";
	}
	std::cout << std::endl;

	if (!pend.empty())
	{
		std::cout << "Inserting pend into main\n";
		insert_pend(main, pend);
	}

	// Mettre a jour _vec avec main
	_vec.clear();
	for (auto it = main.begin(); it != main.end(); it++)
	{
		_vec.insert(_vec.end(), (*it).second.begin(), (*it).second.end());
	}

	// Adding the remains to _vec
	_vec.insert(_vec.end(), remains.begin(), remains.end());
	std::cout << "Vector updated with main and remains\n";
	if (_vec.size() != _size)
	{
		std::cerr << "Error: _vec size mismatch after insertion. Expected: " << _size << ", Actual: " << _vec.size() << std::endl;
		return;
	}
}

// void	PmergeMe::insert_deque(unsigned int elem_size)
// {}

#pragma endregion private_methods
// -------------------------------------------------------------------------- //

// ------------------------------ PUBLIC METHODS ---------------------------- //
#pragma region public_methods

// ______________________________ Utils _____________________________________ //
#pragma region utils
void PmergeMe::incr_nb_comps() { _nb_comps++; }

// Returns the maximum number of comparisons for a given size
// This is based on the formula derived from the Ford-Johnson algorithm
unsigned int PmergeMe::get_max_nb_comps(unsigned int size) const
{
	int sum = 0;
	for (int k = 1; k <= size; ++k)
	{
		double value = (3.0 / 4.0) * k;
		sum += static_cast<int>(ceil(log2(value)));
	}
	return sum;
}

// Returns the nth Jacobsthal number
long PmergeMe::get_nth_jacobsthal(unsigned int n) const
{
	if (n == 0)
		return (0);
	if (n == 1)
		return (1);
	return ((pow(2, n) - pow(-1, n)) / 3);
}

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
#pragma endregion utils
// __________________________________________________________________________ //

// Sort _vec following Ford-Johnson algo
void PmergeMe::sort_vector(unsigned int pair_size)
{
	sort_pairs<std::vector<int>>(_vec, pair_size);
	std::cout << "Pairs sorted with pair size: " << pair_size << std::endl;
	display_vec();
	if (pair_size <= _size / 2)
	{
		sort_vector(pair_size * 2);
		insert_vec(pair_size / 2);
	}
}

void PmergeMe::sort_deque(unsigned int pair_size)
{
	// sort_pairs<std::deque<int>>(pair_size);
	// if (pair_size <= _size / 2)
	// {
	// 	sort_deque(pair_size * 2);
	// 	insert_deque(pair_size / 2);
	// }
}

#pragma endregion public_methods
// -------------------------------------------------------------------------- //

// ############################## OPERATORS ######################################################//

PmergeMe &PmergeMe::operator=(const PmergeMe &copy)
{
	if (this != &copy)
	{
		_vec = copy._vec; // Check si ca marche ca
		_deq = copy._deq;
		_nb_comps = copy._nb_comps;
		_max_nb_comps = copy._max_nb_comps;
		_size = copy._size;
		std::cout << "PmergeMe object assigned\n";
	}
	return (*this);
}

// ############################## GETTERS ########################################################//

const std::vector<int> &PmergeMe::get_vec() const { return (_vec); }
const std::deque<int> &PmergeMe::get_deq() const { return (_deq); }
const unsigned int PmergeMe::get_nb_comps() const { return (_nb_comps); }
const unsigned int PmergeMe::get_max_nb_comps() const { return (_max_nb_comps); }