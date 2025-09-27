//
// Created by TUO8HC on 8/28/2025.
//

#include "Account.hpp"

#include <iostream>
#include <ostream>

int	Account::_nbAccounts = 0;
int	Account::_totalAmount = 0;
int	Account::_totalNbDeposits = 0;
int	Account::_totalNbWithdrawals = 0;


int	Account::getNbAccounts( void ) {
    return Account::_nbAccounts;
}

int	Account::getTotalAmount( void ) {
    return Account::_totalAmount;
}

int	Account::getNbDeposits( void ) {
    return Account::_totalNbDeposits;
}

int	Account::getNbWithdrawals( void ) {
    return Account::_totalNbWithdrawals;
}
void Account::displayAccountsInfos( void ) {
    std::cout << "account:" << getNbAccounts() << ";total:" << getTotalAmount() << ";deposits:" << getNbDeposits() << ";withdrawals:" << getNbWithdrawals() << "\n";
}

Account::Account(int initial_deposit)
{
    Account::_nbAccounts++;
    Account::_totalAmount += initial_deposit;

    this->_accountIndex = _nbAccounts - 1;
    this->_amount = initial_deposit;
    this->_nbDeposits = 0;
    this->_nbWithdrawals = 0;
    std::cout << "index:" << _accountIndex << ";amount:" << _amount << ";created\n";
}

Account::~Account()
{
    std::cout << "index:" << _accountIndex << ";amount:" << _amount << ";closed\n";
}


void Account::makeDeposit(int deposit)
{
    int p_amount = _amount;
    _amount += deposit;
    Account::_totalAmount += deposit;

    _nbDeposits++;
    Account::_totalNbDeposits += _nbDeposits;

    std::cout << "index:" << _accountIndex << ";p_amount:" << p_amount << ";deposits:" << deposit << ";amount:" << _amount << ";nb_deposits:" << _nbDeposits << "\n";
}

bool Account::makeWithdrawal(int withdrawal)
{
    int p_amount = _amount;
    if(withdrawal < _amount)
    {
        _amount -= withdrawal;
        Account::_totalAmount -= withdrawal;

        _nbWithdrawals++;
        Account::_totalNbWithdrawals += _nbWithdrawals;
        std::cout << "index:" << _accountIndex << ";p_amount:" << p_amount << ";withdrawal:" << withdrawal << ";amount:" << _amount << ";nb_withdrawals:" << _nbDeposits << "\n";
        return true;
    }
    else{
        std::cout << "index:" << _accountIndex << ";p_amount:" << p_amount << ";withdrawal:refused\n";
        return false;
    }
}

void Account::displayStatus( void ) const
{
    std::cout << "index:" << _accountIndex << ";amount:" << _amount << ";deposits:" << _nbDeposits << ";withdrawals:" << _nbWithdrawals << "\n";
}