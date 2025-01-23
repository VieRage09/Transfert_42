/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:32:23 by tlebon            #+#    #+#             */
/*   Updated: 2025/01/23 17:45:04 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

#include "crappy.hpp"

class PhoneBook
{
	private:
			Contact		book[8];
			int			max_contact;
			int			saved_index;
			int			current_saved;
	public:
			PhoneBook();
			~PhoneBook();
			
			void	set_saved_index(int value);
			void	set_current_saved(int value);

			int		get_saved_index();
			int		get_current_saved();

			void	display_saved_contacts();
			void	add_crappy();
			void	search_crappy();
			
};

#endif