/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka <louka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 12:12:18 by louka             #+#    #+#             */
/*   Updated: 2026/08/25 12:17:42 by louka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

int main()
{
    ClapTrap clippy("Clippy");
    ClapTrap bob("Bob");

    clippy.attack("Bob");
    bob.takeDamage(0);

    clippy.takeDamage(5);
    clippy.beRepaired(3);

    clippy.takeDamage(10);
    clippy.attack("Bob");
    clippy.beRepaired(5);

    return 0;
}