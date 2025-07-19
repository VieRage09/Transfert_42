#include "ATarget.hpp"

ATarget::ATarget() {}
ATarget::ATarget(std::string type) : type(type) {}
ATarget::ATarget(const ATarget & copy) {}
ATarget::~ATarget() {}

const std::string & ATarget::getType() const { return (type); };


void    ATarget::getHitBySpell(const ASpell & spell)
{
	std::cout << type << " has been " << spell.getEffects() << "!\n";
}
