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

		// Embeded Class 
		template <typename T>
		class Pair
		{
			private:

				typename T::const_iterator	_start;
				typename T::const_iterator	_finish;

				Pair();

			public:

				Pair(typename T::const_iterator start, typename T::const_iterator finish);
				Pair(const Pair<T> & copy);
				~Pair();

				void	sort_pair();

				const typename T::const_iterator & get_start() const;
				const typename T::const_iterator & get_finish() const;

				Pair<T>&		operator = (const Pair<T>& copy);
		};
	
	private:

		// attributes //
		std::vector<int>	_vec;
		std::deque<int>		_deq;
		size_t				_size;

		// Private Default constructor
		PmergeMe();
		
		// Private Methods
		void	create_pairs(std::vector<Pair<std::vector<int>>> & tab, unsigned int pair_size);
		void	recursive_sort(unsigned int pair_size);
};

template <typename T>
std::ostream&	operator << (std::ostream & os, const PmergeMe::Pair<T>& pair);

#endif // PMERGEME_HPP
