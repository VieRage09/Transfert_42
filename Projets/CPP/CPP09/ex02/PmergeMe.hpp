/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:13:05 by tlebon            #+#    #+#             */
/*   Updated: 2025/06/25 18:20:46 by tlebon           ###   ########.fr       */
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

typedef std::vector<std::pair<int, std::vector<int>>> Vec_pair;
typedef std::deque<std::pair<int, std::deque<int>>> Deq_pair;

class PmergeMe
{
	private:

		// attributes //
		std::vector<int>	_vec;
		std::deque<int>		_deq;
		size_t				_size;

		unsigned int		_nb_comps;
		unsigned int		_max_nb_comps;

		// Private Default constructor
		PmergeMe();
		
		// Private Methods
		template <typename T>
		bool				safe_advance(typename T::iterator pos, unsigned int n) const;	
		template <typename T>
		void				sort_pairs(unsigned int pair_size);
		Vec_pair::iterator	binary_search(Vec_pair &main, const std::pair<int, std::vector<int>> &elem,
										Vec_pair::iterator lower_bound, Vec_pair::iterator upper_bound);
		void				binary_insert(std::pair<int, std::vector<int>> &element, Vec_pair &main);
		void				insert_pend(Vec_pair &main, Vec_pair &a_s, Vec_pair &pend);
		void				insert_vec(unsigned int elem_size);
		void				insert_deque(unsigned int elem_size);

	public:
		// Personnalized constructor
		PmergeMe(char **list);
		// Copy constructor
		PmergeMe(const PmergeMe& copy);
		// Destructor
		~PmergeMe();

		// Methods //
		void			incr_nb_comps();
		unsigned int	get_max_nb_comps(unsigned int size) const;
		long			get_nth_jacobsthal(unsigned int n) const;
		void			display_vec() const;
		void			display_deq() const;
		void			sort_vector(unsigned int pair_size);
		void			sort_deque(unsigned int pair_size);

		// Operators //
		PmergeMe&		operator = (const PmergeMe& copy);

		// Getters //
		const std::vector<int>&		get_vec() const;
		const std::deque<int>&		get_deq() const;
		const unsigned int			get_nb_comps() const;
		const unsigned int			get_max_nb_comps() const;
};

#endif // PMERGEME_HPP
