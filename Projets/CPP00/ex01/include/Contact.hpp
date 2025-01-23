/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:24:34 by tlebon            #+#    #+#             */
/*   Updated: 2025/01/23 18:06:05 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
# define CONTACT_HPP

#include"crappy.hpp"

class Contact{
	
	private:
			std::string	fname;
			std::string	lname;
			std::string	nname;
			std::string	number;
			std::string	secret;
	public:
			Contact();
			Contact(std::string fname, std::string lname, std::string nname,
					std::string number, std::string secret);
			Contact(Contact& tocopy);
			~Contact();

			std::string	get_fname();
			std::string	get_lname();
			std::string	get_nname();
			std::string	get_number();
			std::string	get_secret();

			void	set_fname(std::string str);
			void	set_lname(std::string str);
			void	set_nname(std::string str);
			void	set_number(std::string str);
			void	set_secret(std::string str);

			void	display_contact_infos(bool acred);
			void	update_infos(std::string firstn, std::string lastn,
					std::string nickn, std::string phone, std::string secrt);
};

#endif