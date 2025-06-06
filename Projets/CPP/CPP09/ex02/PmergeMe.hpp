#ifndef	PMERGEME_HPP
#define	PMERGEME_HPP

// includes //
#include <vector>
#include <deque>
#include <iostream>
#include <exception>
#include <algorithm>



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
		bool	safe_advance(std::vector<int>::iterator pos, unsigned int n) const;	
		void	sort_pairs(unsigned int pair_size);
		void	recursive_sort(unsigned int pair_size);

	public:
		// Personnalized constructor
		PmergeMe(bool args, char **list);
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
