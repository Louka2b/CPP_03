/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka <louka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 00:00:00 by copilot          #+#    #+#             */
/*   Updated: 2026/09/01 00:00:00 by copilot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

int main(void)
{
	ScavTrap a("Alice");
	ScavTrap b(a);
	ScavTrap c("Charlie");

	c = a;

	a.attack("Bob");
	a.takeDamage(10);
	a.beRepaired(5);
	a.guardGate();

	return 0;
}