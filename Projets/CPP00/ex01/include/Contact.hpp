/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:24:34 by tlebon            #+#    #+#             */
/*   Updated: 2025/01/22 18:11:10 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"crappy_ph_book.hpp"

#ifndef CONTACT_HPP
# define CONTACT_HPP

class Contact{
	
	private:
			std::string	fname;
			std::string	lname;
			std::string	nname;
			std::string	number;
			std::string	secret;
			std::string	ecret;
	public:
			Contact();
			Contact(std::string fname, std::string lname, std::string nname,
					std::string number, std::string secret);
			Contact(Contact& tocopy);
			~Contact();
			void	display_contact_infos(bool acred);
};

#endif