/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka <louka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 12:47:18 by louka             #+#    #+#             */
/*   Updated: 2026/09/02 12:57:48 by louka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

int main(void)
{
	FragTrap a("Alice");
	FragTrap b(a);
	FragTrap c("Charlie");

	c = a;
	a.attack("Bob");
	a.takeDamage(40);
	a.beRepaired(15);
	a.highFivesGuys();

	return 0;
}
