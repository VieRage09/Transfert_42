/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Account.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:24:04 by tlebon            #+#    #+#             */
/*   Updated: 2025/01/24 19:50:22 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Account.hpp"

void	_displayTimestamp( void );

// Static var definition //////////////////////////////////////////////////////
	int	Account::_nbAccounts = 0;
	int	Account::_totalAmount = 0;
	int	Account::_totalNbDeposits = 0;
	int	Account::_totalNbWithdrawals = 0;

// CONSTRUCTOR & DESTRUCTOR ///////////////////////////////////////////////////
Account::Account (int initial_deposit) : _nbDeposits(0), _nbWithdrawals(0)
{
	_displayTimestamp();
	_accountIndex = _nbAccounts;
	_amount = initial_deposit;
	std::cout	<< " index:" << _accountIndex << ";amount:"
				<< initial_deposit << ";created\n";
				// Il faut ajouter les timestamps
	_nbAccounts++;
	_totalAmount += initial_deposit;
}

Account::~Account( void )
{
	_displayTimestamp();
	std::cout	<< " index:" << _accountIndex << ";amount:"
				<< checkAmount() << ";closed\n";	
}

// GETTERS ////////////////////////////////////////////////////////////////////
int	Account::getNbAccounts( void ){return (_nbAccounts);}
int	Account::getTotalAmount( void ){return (_totalAmount);}
int	Account::getNbDeposits( void ){return (_totalNbDeposits);}
int	Account::getNbWithdrawals( void ){return (_totalNbWithdrawals);}

// METHODS ////////////////////////////////////////////////////////////////////
void	Account::displayAccountsInfos( void )
{
	_displayTimestamp(); // Must be accessed from outside the class ?? maybe ? Supprimer car ne compile pas // Mais ou la mettre ??
	std::cout	<< " accounts:" << getNbAccounts()
				<< ";total:" << getTotalAmount()
				<< ";deposits:" << getNbDeposits()
				<< ";withdrawals:" << getNbWithdrawals() << std::endl;
}

void	Account::makeDeposit( int deposit )
{
	_displayTimestamp();
	std::cout	<< " index:" << _accountIndex
				<< ";p_amount:" << checkAmount()
				<< ";deposit:" << deposit;
	_amount += deposit;
	_totalNbDeposits++;
	_nbDeposits++;
	_totalAmount += deposit;
	std::cout	<< ";amount:" << checkAmount ()
				<< ";nb_deposits:" << _nbDeposits << std::endl;
}

bool	Account::makeWithdrawal( int withdrawal )
{
	_displayTimestamp();
	std::cout	<< " index:" << _accountIndex
				<< ";p_amount:" << checkAmount()
				<< ";withdrawal:";
	if (_amount - withdrawal < 0)
	{
		std::cout << "refused\n";
		return (false);
	}
	_amount -= withdrawal;
	_totalNbWithdrawals++;
	_nbWithdrawals++;
	_totalAmount -= withdrawal;
	std::cout	<< withdrawal << ";amount:" << checkAmount ()
				<< ";nb_withdrawals:" << _nbWithdrawals << std::endl;
	return (true);
}

int		Account::checkAmount( void ) const {return (_amount);}

void	Account::displayStatus( void ) const
{
	_displayTimestamp();
	std::cout	<< " index:" << _accountIndex
				<< ";amount:" << checkAmount()
				<< ";deposits:" << _nbDeposits
				<< ";withdrawal:" << _nbWithdrawals << std::endl;
}

void	_displayTimestamp( void )
{
	time_t	timestamp = time(NULL);
	std:: cout << "[" << ctime(&timestamp) << "]";
}