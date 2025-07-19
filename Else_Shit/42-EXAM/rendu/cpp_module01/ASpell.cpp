#include "ASpell.hpp"

ASpell::ASpell() {}
ASpell::ASpell(std::string name, std::string effects) : name(name), effects(effects) {}
ASpell::ASpell(const ASpell & copy) {}
ASpell::~ASpell() {}

const std::string & ASpell::getName () const { return (name); }
const std::string & ASpell::getEffects() const { return (effects); }
