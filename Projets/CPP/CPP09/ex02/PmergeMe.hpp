/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:13:05 by tlebon            #+#    #+#             */
/*   Updated: 2025/06/10 01:54:32 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PMERGEME_HPP
#define	PMERGEME_HPP

// includes //
#include <vector>
#include <deque>
#include <iostream>
#include <exception>
#include <algorithm>
#include <math.h>

class PmergeMe
{
	private:

		// attributes //
		std::vector<int>	_vec;
		std::deque<int>		_deq;
		size_t				_size;

		// Private Default constructor
		PmergeMe();
		
		// Private Methods
		template <typename T>
		bool	safe_advance(typename T::iterator pos, unsigned int n) const;	
		void	sort_pairs(unsigned int pair_size);

		unsigned int	get_nth_jacobsthal(unsigned int n) const;
		void			binary_insert(std::pair<int, std::vector<int>> &element,
						std::vector<std::pair<int, std::vector<int>>> &main) const;
		void			insert_pend(std::vector<std::pair<int, std::vector<int>>> &main,
										std::vector<std::pair<int, std::vector<int>>> &a_s,
										std::vector<std::pair<int, std::vector<int>>> &pend) const;
		void	recursive_sort(unsigned int pair_size); //Pour _vec uniquement ?
		void	insert_vec(unsigned int elem_size);

	public:
		// Personnalized constructor
		PmergeMe(char **list);
		// Copy constructor
		PmergeMe(const PmergeMe& copy);
		// Destructor
		~PmergeMe();

		// Methods //
		void	display_vec() const;
		void	display_deq() const;
		void	sort_vector();
		void	sort_deque();

		// Operators //
		PmergeMe&		operator = (const PmergeMe& copy);

		// Getters //
		const std::vector<int>&		get_vec() const;
		const std::deque<int>&		get_deq() const;
};

#endif // PMERGEME_HPP
