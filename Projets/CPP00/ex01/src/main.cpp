/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:53:53 by tlebon            #+#    #+#             */
/*   Updated: 2025/01/23 18:50:56 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/crappy.hpp"

enum e_input	assign_choice(std::string input)
{
	if (!input.compare("ADD"))
		return (ADD);
	if (!input.compare("SEARCH"))
		return (SEARCH);
	if (!input.compare("EXIT"))
		return (EXIT);
	return (NONE);
}

void	display_help(bool welcome)
{
	if (welcome)
	{	
		std::cout << "Welcome to the crapy phonebook\n";
		std::cout << "You have 3 options :\n" 
			<< "ADD: To add a contact to the phonebook (Note that since it's a crappy one, you can only store 8 contacts)\n"
			<< "SEARCH: To display all the saved contacts and get more specific infos about them\n"
			<< "EXIT: Duh !\n";
	}
	else
	{
		std::cout << "You have 3 options :\n" 
			<< "ADD\nSEARCH\nEXIT\n";
	}
}

int main(int ac, char **av)
{
	PhoneBook		ph_book;
	enum e_input	choice;
	std::string		input;

	system("clear");
	display_help(true);
	while (true)
	{
		std::cout << "Go ahead my friend: ";
		getline(std::cin, input);
		choice = assign_choice(input);	
		switch (choice)
		{
			case ADD:
				system("clear");
				ph_book.add_crappy();
				break;
			case SEARCH:
				system("clear");
				ph_book.search_crappy();
				break;
			case EXIT:
				std::cout << "You successfuly erased everything dummy\n";
				exit(0);
			default:
				display_help(false);
				break;
		}
	}

	return (0);
}
