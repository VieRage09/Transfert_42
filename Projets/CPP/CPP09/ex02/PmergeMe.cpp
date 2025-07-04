/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:13:02 by tlebon            #+#    #+#             */
/*   Updated: 2025/06/30 19:37:29 by tlebon           ###   ########.fr       */
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
	if (!list)
	{
		std::cerr << "[ERROR] list provided is NULL" << std::endl;
		return;
	}
	while (list[i])
	{
		try
		{
			int	num = std::stoi(list[i]);
			_vec.push_back(num);
			_deq.push_back(num);
		}
		catch(const std::exception& e)
		{
			std::cerr << "[ERROR] " << e.what() << " int overflow" << std::endl;
			exit (EXIT_FAILURE);
		}
		_size++;
		i++;
	}
	_time_vec = 0.0;
	_time_deq = 0.0;
	_vec_comps = 0;
	_deq_comps = 0;
	_nb_comps = 0;
	_max_nb_comps = get_max_nb_comps(_size);
}

PmergeMe::PmergeMe(const PmergeMe &copy)
	: _vec(std::vector<int>(copy._vec)), _deq(std::deque<int>(copy._deq))
{
	_time_vec = copy._time_vec;
	_time_deq = copy._time_deq;
	_vec_comps = copy._vec_comps;
	_deq_comps = copy._deq_comps;
	_nb_comps = copy._nb_comps;
	_max_nb_comps = copy._max_nb_comps;
	_size = copy._size;
}

PmergeMe::~PmergeMe() {}

#pragma endregion constructors
// ############################## METHODS ################################### //

// ------------------------------ PRIVATE METHODS --------------------------- //
#pragma region private_methods

#pragma region template_methods

// Used to check if we can increment pos n times w/o getting past end()
template <typename T>
bool	PmergeMe::safe_advance(typename T::iterator pos, typename T::iterator end, unsigned int n) const
{
	int i = 0;
	for (typename T::iterator it = pos; i < n; it++, i++)
		if (it == end)
			return (false);
	return (true);
}

// Sort blocks of numbers following the first step of FJ algo --> by pairs of elements
template <typename T>
void	PmergeMe::sort_pairs(T & container, unsigned int pair_size)
{
	for (typename T::iterator it = container.begin(); safe_advance<T>(it, container.end(), pair_size); it += pair_size)
	{
		if (pair_size == 2)
		{
			incr_nb_comps();
			if (*it > *(it + 1))
				std::iter_swap(it, it + (pair_size / 2));
		}
		else if (pair_size > 2)
		{
			incr_nb_comps();
			if (*(it + (pair_size / 2) - 1) > *(it + pair_size - 1))
				std::swap_ranges(it, it + (pair_size / 2), it + (pair_size / 2));
		}
	}
}

// Loads the main and pend containers with pairs of index/elements from the input container
// Also loads the remains vector with the elements that do not fit
template <typename T, typename T_pair>
void	PmergeMe::load_utils_containers(T & container, unsigned int elem_size, T_pair & main, T_pair & pend, T & remains)
{
	T	first_b(container.begin(), container.begin() + elem_size);
	T	first_a(container.begin() + elem_size, container.begin() + 2 * elem_size);
	
	if (first_b.empty() || first_a.empty())
	{
		std::cerr << "[ERROR] empty elements loaded in main\n";
		exit(EXIT_FAILURE);
	}
	main.emplace_back(1, first_b);
	main.emplace_back(1, first_a);

	typename T::iterator	it = container.begin() + 2 * elem_size;
	bool 					is_biggest_in_pair = false;
	int 					index = 2;

	for (; safe_advance<T>(it, container.end(), elem_size); it += elem_size)
	{
		T group(it, it + elem_size);
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
	// Keep the trail that do not participate for this round --> the one that cannot form an element
	if (it != container.end())
	{
		for (typename T::iterator it_elem = it; it_elem != container.end(); it_elem++)
			remains.push_back(*it_elem);
	}
}

// Uses binary search to find the position to insert the element in the main container 
template <typename T, typename T_pair>
typename T_pair::iterator	PmergeMe::binary_search(T_pair &main,
										const std::pair<int, T> &elem,
										typename T_pair::iterator lower_bound,
										typename T_pair::iterator upper_bound)
{
	int value = elem.second.back();
	typename T_pair::iterator	first = lower_bound;
	typename T_pair::iterator	last = upper_bound;

	while (first < last)
	{
		typename T_pair::iterator mid = first + (last - first) / 2;
		int mid_value = mid->second.back();
		incr_nb_comps();
		if (value > mid_value)
			first = mid + 1;
		else
			last = mid;
	}
	return first;
}

// Finds the upper bound for the element to be inserted in the main container
// If the upper bound is not found, it uses the last element as a fallback
// Inserts the element in the main container at the correct position
template <typename T, typename T_pair>
void PmergeMe::binary_insert(std::pair<int, T> & elem, T_pair & main)
{
	typename T_pair::iterator insert_pos;
	typename T_pair::iterator upper_bound = main.begin();

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
	}
	insert_pos = binary_search(main, elem, main.begin(), upper_bound);
	main.insert(insert_pos, elem);
}

#pragma endregion template_methods

// Inserts the pend elements into the main container using the Jacobsthal sequence and binary_insert function
// Vector version
void PmergeMe::insert_pend_v(Vec_pair &main, Vec_pair &pend)
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
			binary_insert<std::vector<int>, Vec_pair>(pend[i], main);
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

	load_utils_containers<std::vector<int>>(_vec, elem_size, main, pend, remains);

	if (!pend.empty())
		insert_pend_v(main, pend);

	// Mettre a jour _vec avec main
	_vec.clear();
	for (Vec_pair::iterator it = main.begin(); it != main.end(); it++)
	{
		_vec.insert(_vec.end(), (*it).second.begin(), (*it).second.end());
	}

	// Adding the remains to _vec
	_vec.insert(_vec.end(), remains.begin(), remains.end());
	if (_vec.size() != _size)
	{
		std::cerr << "Error: _vec size mismatch after insertion. Expected: " << _size << ", Actual: " << _vec.size() << std::endl;
		return;
	}
}

// Sort _vec following Ford-Johnson algo
void PmergeMe::sort_vector(unsigned int pair_size)
{
	sort_pairs<std::vector<int>>(_vec, pair_size);
	if (pair_size <= _size / 2)
		sort_vector(pair_size * 2);
	insert_vec(pair_size / 2);
}

// Inserts the pend elements into the main container using the Jacobsthal sequence and binary_insert function
// Deque version
void PmergeMe::insert_pend_d(Deq_pair &main, Deq_pair &pend)
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
			binary_insert<std::deque<int>, Deq_pair>(pend[i], main);
		for (unsigned int j = 0; j < count; ++j)
			pend.pop_front();
		jacobsthal = get_nth_jacobsthal(++n);
	}
}

// Creates and loads 2 deques (main & pend) then insert the pend into main and update _deq in the end
void	PmergeMe::insert_deq(unsigned int elem_size)
{
	Deq_pair main;
	Deq_pair pend;
	std::deque<int> remains;
	
	load_utils_containers<std::deque<int>>(_deq, elem_size, main, pend, remains);	
	
	if (!pend.empty())
		insert_pend_d(main, pend);

	// Mettre a jour _deq avec main
	_deq.clear();
	for (Deq_pair::iterator it = main.begin(); it != main.end(); it++)
	{
		_deq.insert(_deq.end(), (*it).second.begin(), (*it).second.end());
	}
	// Adding the remains to _deq
	_deq.insert(_deq.end(), remains.begin(), remains.end());
	if (_deq.size() != _size)
	{
		std::cerr << "Error: _deq size mismatch after insertion. Expected: " << _size << ", Actual: " << _deq.size() << std::endl;
		return;
	}
}

// Sort _deq following Ford-Johnson algo
void PmergeMe::sort_deque(unsigned int pair_size)
{
	sort_pairs<std::deque<int>>(_deq, pair_size);
	if (pair_size <= _size / 2)
		sort_deque(pair_size * 2);
	insert_deq(pair_size / 2);
}

// Both used to keep track of the number of comparisons made during the sorting process
void			PmergeMe::incr_nb_comps() { _nb_comps++; }
void			PmergeMe::reset_nb_comps() { _nb_comps = 0; }

#pragma endregion private_methods
// -------------------------------------------------------------------------- //

// ------------------------------ PUBLIC METHODS ---------------------------- //
#pragma region public_methods

// ______________________________ Utils _____________________________________ //
#pragma region utils

// Returns the maximum number of comparisons for a given size
// This is based on the formula derived from the Ford-Johnson algorithm
unsigned int	PmergeMe::get_max_nb_comps(unsigned int size) const
{
	int sum = 0;
	for (int k = 1; k <= size; ++k)
	{
		double value = (3.0 / 4.0) * k;
		sum += static_cast<int>(ceil(log2(value)));
	}
	return sum;
}


// Returns the nth number of the Jacobsthal's sequence
long			PmergeMe::get_nth_jacobsthal(unsigned int n) const
{
	if (n == 0)
		return (0);
	if (n == 1)
		return (1);
	return ((pow(2, n) - pow(-1, n)) / 3);
}

// Displays the private attribute _vec
void			PmergeMe::display_vec() const
{
	for (std::vector<int>::const_iterator it = _vec.begin(); it != _vec.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
}

// Displays the private attribute _deq
void			PmergeMe::display_deq() const
{
	for (std::deque<int>::const_iterator it = _deq.begin(); it != _deq.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
}

#pragma endregion utils
// __________________________________________________________________________ //

// Launches the sorting process for both _vec and _deq
// if the containers are already sorted or too small, displays a message and returns
void			PmergeMe::launch_sorts()
{
	if (std::is_sorted(_vec.begin(), _vec.end()) && std::is_sorted(_deq.begin(), _deq.end()))
		return;

	clock_t v_start = clock();
	sort_vector(2);
	clock_t v_end = clock();
	_time_vec = static_cast<double>(v_end - v_start) / CLOCKS_PER_SEC * 1000;
	_vec_comps = _nb_comps;

	reset_nb_comps();

	clock_t d_start = clock();
	sort_deque(2);
	clock_t d_end = clock();
	_time_deq = static_cast<double>(d_end - d_start) / CLOCKS_PER_SEC * 1000;
	_deq_comps = _nb_comps;
}

#pragma endregion public_methods
// -------------------------------------------------------------------------- //

// ############################## OPERATORS ######################################################//

PmergeMe &PmergeMe::operator=(const PmergeMe &copy)
{
	if (this != &copy)
	{
		_vec = copy._vec;
		_deq = copy._deq;
		_time_vec = copy._time_vec;
		_time_deq = copy._time_deq;
		_vec_comps = copy._vec_comps;
		_deq_comps = copy._deq_comps;
		_nb_comps = copy._nb_comps;
		_max_nb_comps = copy._max_nb_comps;
		_size = copy._size;
		std::cout << "PmergeMe object assigned\n";
	}
	return (*this);
}

// ############################## GETTERS ########################################################//
#pragma region getters

const std::vector<int>	&PmergeMe::get_vec() const { return (_vec); }
const std::deque<int>	&PmergeMe::get_deq() const { return (_deq); }
const double			PmergeMe::get_time_vec() const { return (_time_vec); }
const double			PmergeMe::get_time_deq() const { return (_time_deq); }
const unsigned int		PmergeMe::get_vec_comps() const { return (_vec_comps); }
const unsigned int		PmergeMe::get_deq_comps() const { return (_deq_comps); }
const unsigned int		PmergeMe::get_max_nb_comps() const { return (_max_nb_comps); }
const size_t 			PmergeMe::get_size() const { return (_size); }

#pragma endregion getters