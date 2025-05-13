#include "RPN.hpp"

// CONSTRUCTORS & DESTRUCTORS //

RPN::RPN() { std::cout << "RPN instanciated\n"; }

RPN::RPN(const RPN &copy)
{
	_rpn = copy._rpn;
	std::cout << "RPN copied\n";
}

RPN::~RPN() { std::cout << "RPN destroyed\n"; }

// METHODS //

bool RPN::valid_char(char c) const
{
	return (isdigit(c) || is_opera(c));
}

bool RPN::is_opera(char c) const
{
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

int RPN::rec_calculus(char top)
{
	int first;
	int second;

	try
	{
		switch (top)
		{
		case '+':
			_rpn.pop();
			first = _rpn.top();
			if (is_opera(first))
			{
				first = rec_calculus(first);
				return (rec_calculus(_rpn.top()) + first);
			}
			_rpn.pop();
			second = _rpn.top();
			if (is_opera(second))
				return (rec_calculus(second) + first);
			_rpn.pop();
			return (second + first);

		case '-':
			_rpn.pop();
			first = _rpn.top();
			if (is_opera(first))
			{
				first = rec_calculus(first);
				return (rec_calculus(_rpn.top()) - first);
			}
			_rpn.pop();
			second = _rpn.top();
			if (is_opera(second))
				return (rec_calculus(second) - first);
			_rpn.pop();
			return (second - first);

		case '*':
			_rpn.pop();
			first = _rpn.top();
			if (is_opera(first))
			{
				first = rec_calculus(first);
				return (rec_calculus(_rpn.top()) * first);
			}
			_rpn.pop();
			second = _rpn.top();
			if (is_opera(second))
				return (rec_calculus(second) * first);
			_rpn.pop();
			return (second * first);

		case '/':
			_rpn.pop();
			first = _rpn.top();
			if (is_opera(first))
			{
				first = rec_calculus(first);
				return (rec_calculus(_rpn.top()) / first);
			}
			_rpn.pop();
			second = _rpn.top();
			if (is_opera(second))
				return (rec_calculus(second) / first);
			_rpn.pop();
			return (second / first);
		
		default:
			throw std::runtime_error("Error in calculating\n");
			return (0);
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}
	return (0);
}

int RPN::calculate_rpn(void)
{
	if (_rpn.empty())
		throw std::runtime_error("empty stack\n");
	if (_rpn.size() == 1)
		return (_rpn.top());
	return (rec_calculus(_rpn.top()));
}

bool RPN::load_stack(std::string s)
{
	if (s.empty())
		return (std::cerr << "Error: empty string\n", false);
	while (!_rpn.empty())
		_rpn.pop();
	for (char c : s)
	{
		if (isspace(c))
			continue;
		if (!valid_char(c))
			return (std::cerr << "Error: invalid char\n", false);
		if (isdigit(c))
			_rpn.push(c - '0');
		else
			_rpn.push(c);
	}
	return (true);
}

// // OPERATORS //

// RPN& RPN::operator = (const RPN& copy)
// {
// 	if (this != &copy)
// 	{

// 	}
// 	return (*this);
// }

// // GETTERS //

// const std::stack<int>&	RPN::get_rpn() const { return ( _rpn );}

// // GETTERS //

// void	RPN::set_rpn(std::stack<int>& value) { this->_rpn = value; }
