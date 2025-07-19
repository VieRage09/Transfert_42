#include "Warlock.hpp"

Warlock::Warlock(std::string name, std::string title) : name(name), title(title)
{
	std::cout << name << ": This looks like another boring day." << std::endl;
}

Warlock::~Warlock() { std::cout << name << ": My job here is done!" << std::endl; }

void	Warlock::introduce() const { std::cout << name << ": I am " << name << ", " << title << "!\n"; } 

const std::string & Warlock::getName() const { return (name); }
const std::string & Warlock::getTitle() const { return (title); }

void	Warlock::setTitle(const std::string & value) {title = value;}
