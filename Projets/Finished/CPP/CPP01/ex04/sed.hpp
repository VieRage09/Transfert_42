/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sed.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:15:23 by tlebon            #+#    #+#             */
/*   Updated: 2025/01/29 16:25:37 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SED_H
#define	SED_H

#include <iostream>
#include <fstream>

void	sedlike(std::string infile, std::string to_replace, std::string replacement);

#endif