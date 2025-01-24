/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:15:18 by tlebon            #+#    #+#             */
/*   Updated: 2025/01/24 13:13:21 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/crappy.hpp"

// CONSTRUCTEURS & DESTRUCTEUR /////////////////////////////////////////////////

Contact::Contact(): fname("John"), lname("Smith"), nname("Smitty"), number("008"), secret("MI6"){}

Contact::Contact(std::string fname, std::string lname, std::string nname,
					std::string number, std::string secret)
{
	this->fname = fname;
	this->lname = lname;
	this->nname = nname;
	this->number= number;
	this->secret= secret;
}

Contact::Contact(Contact& tocopy)
{
	this->fname = tocopy.fname;
	this->lname = tocopy.lname;
	this->nname = tocopy.nname;
	this->number= tocopy.number;
	this->secret= tocopy.secret;
}

Contact::~Contact(){}

// GETTERS ////////////////////////////////////////////////////////////////////

std::string	Contact::get_fname()
{
	return (this->fname);
}

std::string	Contact::get_lname()
{
	return (this->lname);
}

std::string	Contact::get_nname()
{
	return (this->nname);
}

std::string	Contact::get_number()
{
	return (this->number);
}

std::string	Contact::get_secret()
{
	return (this->secret);
}

// SETTERS ////////////////////////////////////////////////////////////////////

void	Contact::set_fname(std::string str)
{
	this->fname = str;
}

void	Contact::set_lname(std::string str)
{
	this->lname = str;
}

void	Contact::set_nname(std::string str)
{
	this->nname = str;
}

void	Contact::set_number(std::string str)
{
	this->number = str;
}

void	Contact::set_secret(std::string str)
{
	this->secret = str;
}

// METHODES ///////////////////////////////////////////////////////////////////

void	Contact::display_contact_infos(bool acred)
{
	std::cout << "First name: " << fname << std::endl;
	std::cout << "Last name: " << lname << std::endl;
	std::cout << "Nickname: " << nname << std::endl;
	std::cout << "Phone number: " << number << std::endl;
	if (acred)
		std::cout << "Darkest secret: " << secret<< std::endl;
}

void	Contact::update_infos(std::string firstn, std::string lastn,
			std::string nickn, std::string phone, std::string secrt)
{
	set_fname(firstn);
	set_lname(lastn);
	set_nname(nickn);
	set_number(phone);
	set_secret(secrt);
}