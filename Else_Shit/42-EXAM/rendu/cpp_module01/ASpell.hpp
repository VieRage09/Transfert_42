#include <iostream>

class ASpell
{
	private:
		std::string name;
		std::string effects;
	public:
		ASpell();
		ASpell(std::string name, std::string effects);
		ASpell(const ASpell & copy);
		~ASpell();

		const std::string & getName() const;
		const std::string & getEffects() const;
		
		virtual ASpell * clone () = 0 const;
	

};
