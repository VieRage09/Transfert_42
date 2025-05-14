#ifndef	RPN_HPP
#define	RPN_HPP

// includes //
#include <stack>
#include <iostream>
#include <algorithm>

class RPN
{
	private:

		// attributes //
		std::stack<int>		_rpn;

		// methods //
		bool	valid_char(char c) const;
		bool	is_opera(char c) const;
		int		rec_calculus(char ope);

	public:
		// Default constructor
		RPN();
		// Copy constructor
		RPN(const RPN& copy);
		// Destructor
		~RPN();

		// Methods //
		bool	load_stack(std::string s);
		int		calculate_rpn( void ); // Throw

		// Operators //
		RPN&				operator = (const RPN& copy);

};

#endif // RPN_HPP
