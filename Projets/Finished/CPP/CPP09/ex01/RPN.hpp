#ifndef	RPN_HPP
#define	RPN_HPP

// includes //
#include <stack>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <climits>

class RPN
{
	private:

		// attributes //
		std::stack<int>		_rpn;

		// methods //
		bool	valid_char(char c) const;
		bool	is_valid_str(const std::string & str);
		bool	is_opera(char c) const;
		void	calculation(char c);
	public:

		// Default constructor
		RPN();
		// Copy constructor
		RPN(const RPN& copy);
		// Destructor
		~RPN();

		// Methods //
		int		calculate_rpn(const std::string & s);

		// Operators //
		RPN&				operator = (const RPN& copy);

};

#endif // RPN_HPP
