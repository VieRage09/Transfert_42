/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:42:15 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/06 14:49:54 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/PhoneBook.hpp"

// CONSTRUCTEUR & DESCTRUCTEUR ////////////////////////////////////////////////
PhoneBook::PhoneBook(): max_contact(8), saved_index(0), current_saved(0) {}

PhoneBook::~PhoneBook() {}

// SETTERS ////////////////////////////////////////////////////////////////////
void	PhoneBook::set_saved_index(int value) {saved_index = value;}

void	PhoneBook::set_current_saved(int value) {current_saved = value;}

// GETTERS ////////////////////////////////////////////////////////////////////
int	PhoneBook::get_saved_index() {return (saved_index);}

int	PhoneBook::get_current_saved() {return (current_saved);}

// METHODS ////////////////////////////////////////////////////////////////////
void	PhoneBook::display_saved_contacts()
{
	for(int i = 0; i < current_saved; i++)
	{
		book[i].display_contact_infos(true);
		std::cout << std::endl;
	}	
}

static void	crop_string(std::string& str)
{
	str.erase(0, str.find_first_not_of(" \t"));
	str.erase(str.find_last_not_of(" \t") + 1);
}

static void	collect(std::string& info, std::string prompt, bool num)
{
	do
	{
		std::cout << prompt;
		if (!getline(std::cin, info))
			return ;
		crop_string(info);
	} while (info.empty() || (num && info.find_first_not_of("0123456789") != std::string::npos));
}

void	PhoneBook::add_crappy()
{
	std::string	firstname;
	std::string	lastname;
	std::string	nickname;
	std::string	phone;
	std::string	darks;

	collect(firstname, "Enter firstname: ", 0);
	collect(lastname, "Enter lastname: ", 0);
	collect(nickname, "Enter nickname: ", 0);
	collect(phone, "Enter phone number: ", 1);
	collect(darks, "Enter darkest secret: ", 0);

	if (current_saved < 8)
	{
		book[saved_index].update_infos(firstname, lastname, nickname, phone, darks);
		saved_index++;
		current_saved++;
	}
	else
	{
		if (saved_index > 7)
			saved_index = 0;
		book[saved_index].update_infos(firstname, lastname, nickname, phone, darks);
		saved_index++;
	}
}

static void	justify_str(std::string& str)
{
	if (str.size() > 10)
	{
		str.erase(9);
		str += '.';
	}
	else
	{
		while (str.size() < 10)
			str = ' ' + str;
	}
}

static void	prepare_strings(int i, Contact contact, std::string& index, std::string& first, std::string& last, std::string& nick)
{
	index = "          ";
	index[9] = i + 48;
	first = contact.get_fname();
	justify_str(first);
	last = contact.get_lname();
	justify_str(last);
	nick = contact.get_nname();
	justify_str(nick);
}
void	PhoneBook::search_crappy()
{
	std::string	prep_index;
	std::string	prep_fname;
	std::string	prep_lname;
	std::string	prep_nname;
	std::string	input;

	if (current_saved < 1)
	{
		std::cout << "No saved contacts\n";
		return ;
	}
	for(int i = 0; i < current_saved; i++)
	{
		prepare_strings(i, book[i], prep_index, prep_fname, prep_lname, prep_nname);
		std::cout << prep_index << "|" << prep_fname << "|" << prep_lname << "|" << prep_nname << std::endl;
	}
	do
	{
		std::cout << "Type in contact index: ";
		getline(std::cin, input);
		crop_string(input);
	} while (input.size() > 1 || input[0] >= current_saved + '0' || input[0] < '0');
	book[input[0] - '0'].display_contact_infos(true);
}
