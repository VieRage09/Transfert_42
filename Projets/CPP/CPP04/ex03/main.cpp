/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:07:42 by tlebon            #+#    #+#             */
/*   Updated: 2025/03/10 18:57:27 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hgroup.hpp"

// int main(void)
// {
// 	MateriaSource *src = new MateriaSource();
// 	src->learnMateria(new Ice());
// 	src->learnMateria(new Cure());
// 	ICharacter *me = new Character("me");
// 	AMateria *tmp;

// 	tmp = src->createMateria("ice");
// 	me->equip(tmp);
// 	tmp = src->createMateria("cure");
// 	me->equip(tmp);
// 	ICharacter *bob = new Character("bob");
// 	me->use(0, *bob);
// 	me->use(1, *bob);
// 	delete bob;
// 	delete me;
// 	delete src;

// 	return (0);
// }

int	main()
{
	std::cout << "Test AMateria Ice and Cure\n\n";
	AMateria *	a = new Ice();
	AMateria *	b = new Cure();
	AMateria *	c;

	std::cout << "\nTest assignement operator for Ice and Cure\n\n";
	c = a;
	std::cout << "c type = " << c->getType() << std::endl;
	c = b;
	std::cout << "c type = " << c->getType() << std::endl;

	std::cout << "\nTest Character (Creation + empty inventory and floor)\n\n";
	ICharacter *	bob = new Character("Bob");
	ICharacter *	tarzan = new Character("Tarzan");
	bob->print_inventory();
	bob->print_floor();

	std::cout << "\nTest use function for Ice and Cure\n\n";
	a->use(*tarzan);
	b->use(*tarzan);

	std::cout << "\nTest Character equip\n\n";
	bob->equip(a);
	bob->equip(b);
	bob->equip(c);
	bob->print_inventory();
	bob->equip(a);
	bob->equip(b);
	bob->equip(NULL);
	bob->print_inventory();

	std::cout << "\nTest Character use\n\n";
	bob->use(5, *tarzan);
	bob->use(-1, *tarzan);
	bob->use(0, *tarzan);
	bob->use(1, *tarzan);

	std::cout << "\nTest Character unequip\n\n";
	bob->unequip(-1);
	bob->unequip(5);
	bob->print_inventory();
	bob->unequip(2);
	bob->print_inventory();
	bob->print_floor();
	bob->unequip(2);

	std::cout << "\nTest Character assignation operator\n\n";
	ICharacter *	cpy = bob;
	cpy->print_inventory();
	cpy->print_floor();
	delete a;
	cpy->use(1, *tarzan);

	std::cout << "\nTest MateriaSource\n\n";
	MateriaSource *	src = new MateriaSource();
	src->printBook();
	src->learnMateria(c);
	src->learnMateria(b);
	src->learnMateria(c);
	src->learnMateria(b);
	src->printBook();
	AMateria *	ex;
	ex = src->createMateria("ice");
	ex = src->createMateria("cure");
	std::cout << "Materia created = " << ex->getType() << std::endl;
}