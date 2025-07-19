#include <iostream>

class Warlock
{
	private:
		std::string	name;
		std::string	title;
	
		Warlock();
		Warlock(const Warlock & copy);
		Warlock & operator = (const Warlock & copy);

	public:
		Warlock(std::string name, std::string title);
		~Warlock();

		void	introduce() const;

		const std::string &	getName () const;
		const std::string &	getTitle () const;

		void	setTitle(const std::string & value);

};
