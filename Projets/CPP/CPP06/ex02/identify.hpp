/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 00:08:49 by tlebon            #+#    #+#             */
/*   Updated: 2025/04/27 00:11:21 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IDENTIFY_HPP
# define IDENTIFY_HPP

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

Base	*	generate( void );
void		identify(Base * p);
void		identify(Base & p);

#endif 
