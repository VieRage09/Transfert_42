#include "RPN.hpp"

// CONSTRUCTORS & DESTRUCTORS //

RPN::RPN() {}

RPN::RPN(const RPN &copy) : _rpn(copy._rpn) {}

RPN::~RPN() {}

// METHODS //

bool	RPN::valid_char(char c) const { return (isdigit(c) || is_opera(c)); }

bool	RPN::is_valid_str(const std::string & str)
{
	for (int i = 0; i < str.size(); i++)
	{
		if (!valid_char(str[i]))
			return (false);
	}
	return (true);
}

bool	RPN::is_opera(char c) const { return (c == '+' || c == '-' || c == '*' || c == '/'); }

void	RPN::calculation(char ope)
{
	long long	rhs;
	long long	lhs;
	long long	res;

	if (_rpn.size() < 2)
		throw std::runtime_error("[ERROR] Invalid RPN expression: too many operators");
	if (ope == '/' && _rpn.top() == 0)
		throw std::runtime_error("[ERROR] Division by zero not allowed");
	rhs = _rpn.top();
	_rpn.pop();
	lhs = _rpn.top();
	_rpn.pop();
	switch (ope)
	{
		case '+':
			res = lhs + rhs;
			break;
		case '-':
			res = lhs - rhs;
			break;
		case '*':
			res = lhs * rhs;
			break;
		case '/':
			res = lhs / rhs;
			break;
	}
	if (res < INT_MIN || res > INT_MAX)
		throw std::runtime_error("[ERROR] Int Overflow");
	_rpn.push(static_cast<int>(res));
}

int		RPN::calculate_rpn(const std::string & s)
{
	std::stringstream 	ss;
	std::string			tmp;
	int					i;
	char				ope;

	if (s.empty() || std::all_of(s.begin(), s.end(), isspace))
		throw std::runtime_error("[ERROR] Empty RPN expression");

	ss << s;
	while (!ss.eof())
	{
		ss >> tmp;
		if (!is_valid_str(tmp))
			throw std::runtime_error("[ERROR] Invalid char");
		if (std::stringstream(tmp) >> i)
		{
			if (i < 0 || i > 9)
				throw std::runtime_error("[ERROR] Number must be [0, 9]");
			_rpn.push(i);
		}
		else if (std::stringstream(tmp) >> ope && is_opera(ope))
		{
			if (tmp.size() != 1)
				throw std::runtime_error("[ERROR] Invalid RPN expression: unseparated operators");
			calculation(ope);
		}
		tmp = "";
	}
	if (_rpn.size() != 1)
		throw std::runtime_error("[ERROR] Invalid RPN expression: not enough operators");
	return (_rpn.top());
}

// // OPERATORS //

RPN& RPN::operator = (const RPN& copy)
{
	if (this != &copy)
	{
		_rpn = copy._rpn;
		std::cout << "RPN assigned\n";
	}
	return (*this);
}
