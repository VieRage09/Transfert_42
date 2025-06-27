/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:13:05 by tlebon            #+#    #+#             */
/*   Updated: 2025/06/27 13:44:16 by tlebon           ###   ########.fr       */
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
		template <typename T> bool	safe_advance(typename T::iterator pos, typename T::iterator end, unsigned int n) const;	
		template <typename T> void	sort_pairs(T & container, unsigned int pair_size);

		template <typename T, typename T_pair>
		void						load_utils_containers(T & container, unsigned int elem_size,
															T_pair & main, T_pair & pend, T & remains);
		template <typename T, typename T_pair>
		typename T_pair::iterator	binary_search(T_pair & main, const std::pair<int, T> & elem,
										typename T_pair::iterator lower_bound, typename T_pair::iterator upper_bound);
		template <typename T, typename T_pair>
		void						binary_insert(std::pair<int, T> &element, T_pair &main);

		void						insert_pend_v(Vec_pair &main, Vec_pair &pend);
		void 						insert_pend_d(Deq_pair &main, Deq_pair &pend);
		void						insert_vec(unsigned int elem_size);
		void						insert_deq(unsigned int elem_size);

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
		void			reset_nb_comps();
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
		const size_t				get_size() const;
};

#endif // PMERGEME_HPP
