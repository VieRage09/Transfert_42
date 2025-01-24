/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Account.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:24:04 by tlebon            #+#    #+#             */
/*   Updated: 2025/01/24 18:03:01 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Account.hpp"

// Static var definition //////////////////////////////////////////////////////
	int	Account::_nbAccounts = 0;
	int	Account::_totalAmount = 0;
	int	Account::_totalNbDeposits = 0;
	int	Account::_totalNbWithdrawals = 0;

// CONSTRUCTOR & DESTRUCTOR ///////////////////////////////////////////////////
Account::Account (int initial_deposit) : _nbDeposits(0), _nbWithdrawals(0)
{
	_accountIndex = _nbAccounts;
	_amount = initial_deposit;
	std::cout	<< " index:" << _accountIndex << ";amount:"
				<< initial_deposit << ";created\n";
	_nbAccounts++;
}

Account::~Account( void ){}

// GETTERS ////////////////////////////////////////////////////////////////////
int	Account::getNbAccounts( void ){return (_nbAccounts);}
int	Account::getTotalAmount( void ){return (_totalAmount);}
int	Account::getNbDeposits( void ){return (_totalNbDeposits);}
int	Account::getNbWithdrawals( void ){return (_totalNbWithdrawals);}

// METHODS ////////////////////////////////////////////////////////////////////
void	Account::displayAccountsInfos( void )
{

}

void	Account::makeDeposit( int deposit )
{

}

bool	Account::makeWithdrawal( int withdrawal )
{
	return (true);
}

int		Account::checkAmount( void ) const
{
	return (0);
}

void	Account::displayStatus( void ) const
{
	
}