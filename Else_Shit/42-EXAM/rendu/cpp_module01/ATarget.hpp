#include <iostream>

class ASpell;

class ATarget
{
	private:
		std::string type;
	public:
		ATarget();
		ATarget(std::string type);
		ATarget(const ATarget * copy);
		~ATarget();

		const std::string &	getType() const;

		ATarget * clone () const = 0;

		void	getHitBySpell (const ASpell & spell);
};
