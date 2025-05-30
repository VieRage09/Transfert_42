#ifndef	PMERGEME_HPP
#define	PMERGEME_HPP

// includes //
#include <vector>
#include <deque>
#include <iostream>
#include <exception>

class PmergeMe
{
	private:

		// attributes //
		std::vector<int>	_vec;
		std::deque<int>		_deq;

		// Default constructor
		PmergeMe();

	public:
		// Personnalized constructor
		PmergeMe(bool args, char **list);
		// Copy constructor
		PmergeMe(const PmergeMe& copy);
		// Destructor
		~PmergeMe();

		// Methods //
		void	display_containers() const;
		void	sort_vector();
		void	sort_deque();

		// Operators //
		PmergeMe&		operator = (const PmergeMe& copy);

		// Getters //
		const std::vector<int>&		get_vec() const;
		const std::deque<int>&		get_deq() const;

};

#endif // PMERGEME_HPP
