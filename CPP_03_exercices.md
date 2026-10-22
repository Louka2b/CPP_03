# C++ 03 : explication des 3 exercices

Ce module porte sur les notions de classes, d'héritage et de constructeur/copieur en C++.

## Ex00 : ClapTrap

### Objectif
Créer une classe `ClapTrap` qui représente un personnage de jeu avec :
- un nom
- des points de vie (`_hitPoints`)
- des points d'énergie (`_energyPoints`)
- des dégâts d'attaque (`_attackDamage`)

### Ce que fait la classe
`
ClapTrap` contient 3 méthodes principales :
- `attack(const std::string& target)` : attaque une cible si le robot a encore de l'énergie et s'il n'est pas détruit.
- `takeDamage(unsigned int amount)` : perd des points de vie.
- `beRepaired(unsigned int amount)` : récupère des points de vie en consommant de l'énergie.

### Règles importantes
- Si les points de vie valent 0, le robot est détruit.
- Une attaque ne peut pas être faite si l'énergie est à 0.
- Une réparation ne peut pas être faite si le robot est détruit.
- Le constructeur par défaut initialise des valeurs de base.
- Le constructeur avec nom permet de donner un nom au robot.
- Le constructeur de copie et l'opérateur d'affectation permettent de copier un objet proprement.

### Ce que tu dois retenir
Ex00 sert à maîtriser les bases d'une classe avec attributs, méthodes, constructeurs et logique de jeu. C'est la base sur laquelle les exercices suivants s'appuient.

---

## Ex01 : ScavTrap

### Objectif
Créer une classe `ScavTrap` qui hérite de `ClapTrap`.

### Idée de l'héritage
`ScavTrap` reprend les attributs et méthodes de `ClapTrap`, mais ajoute sa propre logique spécifique.

### Ce qui change par rapport à `ClapTrap`
`ScavTrap` a des statistiques différentes :
- 100 points de vie
- 50 points d'énergie
- 20 dégâts d'attaque

Il redéfinit aussi :
- `attack(const std::string& target)`
- `guardGate()`

### La méthode `guardGate()`
Cette méthode représente un mode spécial :

`ScavTrap` "passe en mode Gate keeper".

C'est une capacité propre à cette classe. On l'appelle pour montrer qu'un `ScavTrap` a un comportement particulier, différent d'un simple `ClapTrap`.

### Pourquoi c'est utile
Tu apprends ici :
- l'héritage en C++
- la surcharge de méthodes
- l'initialisation des attributs dérivés
- l'appel du constructeur de base

### Exemple conceptuel
```cpp
ScavTrap a("Alice");
a.guardGate();
a.attack("Bob");
```
Ici, `a` est un `ScavTrap`, donc il a les caractéristiques d'un `ClapTrap` + des fonctions propres.

---

## Ex02 : FragTrap

### Objectif
Créer une autre classe dérivée de `ClapTrap`, cette fois `FragTrap`.

### Différence avec `ScavTrap`
`FragTrap` est encore plus offensif :
- 100 points de vie
- 100 points d'énergie
- 30 dégâts d'attaque

### Méthodes spécifiques
Il redéfinit :
- `attack(const std::string& target)`
- `highFivesGuys(void)`

### La méthode `highFivesGuys()`
Cette méthode affiche un message du type :

"FragTrap demande un high five positif !"

C'est une technique pour montrer qu'un `FragTrap` a un comportement particulier, plus joyeux et plus "agressif" que `ScavTrap`.

### Ce que tu dois comprendre
Ex02 montre qu'un même parent (`ClapTrap`) peut avoir plusieurs enfants (`ScavTrap`, `FragTrap`) avec des statistiques et capacités différentes.

C'est le principe fondamental de l'héritage :
- une classe mère fournit le squelette de base
- les classes filles ajoutent ou modifient le comportement

---

## Résumé rapide

### Ex00
Tu construis la base : `ClapTrap`

### Ex01
Tu crées une classe fille : `ScavTrap`
- héritage
- stats spécifiques
- `guardGate()`

### Ex02
Tu crées une autre classe fille : `FragTrap`
- héritage
- stats spécifiques
- `highFivesGuys()`

---

## Le point important du module
Les 3 exercices introduisent la notion suivante :

"Un objet peut hériter d'un autre objet, puis avoir ses propres caractéristiques et méthodes, tout en gardant les bases de la classe mère."

C'est une base très importante pour la programmation orientée objet en C++.

Si tu veux, je peux aussi te faire un fichier `README.md` plus simple et encore plus visuel, avec un schéma de classe et des exemples de code à compléter.
