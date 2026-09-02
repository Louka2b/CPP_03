/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka <louka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 12:47:13 by louka             #+#    #+#             */
/*   Updated: 2026/09/02 12:57:41 by louka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

FragTrap::FragTrap() : ClapTrap("Default")
{
	this->_hitPoints = 100;
	this->_energyPoints = 100;
	this->_attackDamage = 30;
	std::cout << "FragTrap default constructor called" << std::endl;
}

FragTrap::FragTrap(const std::string& name) : ClapTrap(name)
{
	this->_hitPoints = 100;
	this->_energyPoints = 100;
	this->_attackDamage = 30;
	std::cout << "FragTrap string constructor called for " << this->_name << std::endl;
}

FragTrap::FragTrap(const FragTrap& other) : ClapTrap(other)
{
	std::cout << "FragTrap copy constructor called" << std::endl;
}

FragTrap& FragTrap::operator=(const FragTrap& other)
{
	std::cout << "FragTrap copy assignment operator called" << std::endl;
	if (this != &other)
		ClapTrap::operator=(other);
	return *this;
}

FragTrap::~FragTrap()
{
	std::cout << "FragTrap destructor called for " << this->_name << std::endl;
}

void FragTrap::attack(const std::string& target)
{
	if (this->_hitPoints == 0)
	{
		std::cout << "FragTrap " << this->_name << " cannot attack because it is destroyed!" << std::endl;
		return;
	}
	if (this->_energyPoints == 0)
	{
		std::cout << "FragTrap " << this->_name << " has no energy left to attack!" << std::endl;
		return;
	}
	this->_energyPoints--;
	std::cout << "FragTrap " << this->_name << " attacks " << target
			  << ", causing " << this->_attackDamage << " points of damage!" << std::endl;
}

void FragTrap::highFivesGuys(void)
{
	std::cout << "FragTrap " << this->_name << " requests a positive high five!" << std::endl;
}
