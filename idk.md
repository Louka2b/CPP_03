# Comprendre le projet CPP-03

Ce projet montre progressivement la programmation orientée objet en C++ avec des robots de combat. Il est divise en trois exercices :

- `ex00` : creation de la classe de base `ClapTrap`.
- `ex01` : ajout de l'heritage avec `ScavTrap`.
- `ex02` : ajout d'une deuxieme classe fille avec `FragTrap`.

Chaque exercice est autonome et possede son propre `Makefile`.

## 1. Notions generales

### Classe et objet

Une **classe** definit la structure et les comportements d'un type d'objet. Un **objet** est une instance de cette classe.

Par exemple :

```cpp
ClapTrap clippy("Clippy");
```

Cette ligne cree un objet `ClapTrap` nomme `clippy`, dont le nom interne vaut `"Clippy"`.

### Declaration et definition

Les fichiers `.hpp` contiennent principalement les declarations : les attributs et les prototypes des fonctions.

Les fichiers `.cpp` contiennent les definitions : le code execute par les fonctions.

Exemple :

```cpp
// ClapTrap.hpp
void attack(const std::string& target);

// ClapTrap.cpp
void ClapTrap::attack(const std::string& target)
{
    // implementation
}
```

### Encapsulation

Dans `ex00`, les attributs de `ClapTrap` sont `private`. Ils ne peuvent donc etre utilises directement que par les methodes de `ClapTrap`.

Dans `ex01` et `ex02`, ils deviennent `protected`. Cela permet aux classes filles `ScavTrap` et `FragTrap` de modifier leurs propres points de vie, energie et degats.

### Include guards

Chaque header contient une protection comme :

```cpp
#ifndef CLAPTRAP_HPP
# define CLAPTRAP_HPP

// declaration de la classe

#endif
```

Elle empeche le meme header d'etre inclus plusieurs fois pendant la compilation.

## 2. Fonctionnement commun de ClapTrap

La classe `ClapTrap` contient quatre attributs :

| Attribut | Type | Role |
| --- | --- | --- |
| `_name` | `std::string` | Nom du robot |
| `_hitPoints` | `unsigned int` | Points de vie |
| `_energyPoints` | `unsigned int` | Points d'energie disponibles |
| `_attackDamage` | `unsigned int` | Degats infliges par une attaque |

Les valeurs de base sont :

- 10 points de vie ;
- 10 points d'energie ;
- 0 point de degat.

`unsigned int` ne peut pas contenir de valeur negative. C'est adapte pour compter des points de vie ou d'energie.

### Les constructeurs

#### Constructeur par defaut

```cpp
ClapTrap::ClapTrap()
    : _name("Default"), _hitPoints(10), _energyPoints(10), _attackDamage(0)
```

Il cree un robot avec des valeurs par defaut.

La liste apres `:` est une **liste d'initialisation**. Elle initialise directement les attributs avant l'execution du corps du constructeur.

#### Constructeur avec un nom

```cpp
ClapTrap::ClapTrap(const std::string& name)
```

Il donne au robot le nom fourni et initialise les autres valeurs avec les statistiques standards.

Le parametre est une reference constante :

- aucune copie inutile de la chaine n'est necessaire ;
- la fonction ne peut pas modifier `name`.

#### Constructeur de copie

```cpp
ClapTrap::ClapTrap(const ClapTrap& other)
```

Il cree un nouvel objet a partir d'un autre objet existant. Il utilise l'operateur d'affectation pour copier les quatre attributs.

Exemple :

```cpp
ClapTrap original("A");
ClapTrap copie(original);
```

#### Operateur d'affectation

```cpp
ClapTrap& ClapTrap::operator=(const ClapTrap& other)
```

Il copie l'etat d'un objet deja cree vers un autre objet deja existant :

```cpp
ClapTrap a("A");
ClapTrap b("B");
b = a;
```

Le test :

```cpp
if (this != &other)
```

evite de recopier un objet sur lui-meme. La methode retourne `*this`, ce qui permet notamment les affectations en chaine.

#### Destructeur

```cpp
ClapTrap::~ClapTrap()
```

Il est appele automatiquement quand l'objet sort de son scope, par exemple a la fin de `main`. Ici, il affiche un message pour montrer l'ordre de destruction.

Dans `ex01` et `ex02`, le destructeur est `virtual` dans `ClapTrap`. C'est important lorsqu'un objet d'une classe fille peut etre manipule via un pointeur ou une reference vers `ClapTrap` : le bon destructeur sera alors appele.

### Methode `attack`

```cpp
void attack(const std::string& target);
```

Elle effectue les controles suivants :

1. Si le robot a 0 point de vie, il ne peut pas attaquer.
2. Si le robot a 0 point d'energie, il ne peut pas attaquer.
3. Sinon, l'energie diminue de 1.
4. Un message indique la cible et les degats.

Important : la methode affiche les degats, mais elle ne retire pas automatiquement ces degats a la cible. C'est le code appelant qui doit ensuite appeler `takeDamage` sur l'autre robot.

### Methode `takeDamage`

```cpp
void takeDamage(unsigned int amount);
```

Elle retire `amount` points de vie.

Si les degats sont superieurs ou egaux aux points de vie restants, les points de vie sont fixes a 0. Cette condition evite qu'un `unsigned int` passe sous zero.

Un robot deja detruit ne perd plus de points de vie et affiche un message indiquant son etat.

### Methode `beRepaired`

```cpp
void beRepaired(unsigned int amount);
```

Elle effectue les controles suivants :

1. Un robot detruit ne peut pas etre repare.
2. Une reparation consomme 1 point d'energie.
3. Le nombre de points de vie est augmente de `amount`.

Il n'y a pas de maximum de points de vie dans ce code : un robot peut donc depasser ses points de vie initiaux avec plusieurs reparations.

## 3. Exercice 00 : ClapTrap

### Fichiers

- `ex00/ClapTrap.hpp` : declaration de la classe.
- `ex00/ClapTrap.cpp` : constructeurs, destructeur et actions.
- `ex00/main.cpp` : scenario de test.
- `ex00/Makefile` : compilation du programme `claptrap`.

### Scenario de `main.cpp`

```cpp
ClapTrap clippy("Clippy");
ClapTrap bob("Bob");
```

Deux robots sont crees avec 10 HP, 10 points d'energie et 0 degat.

```cpp
clippy.attack("Bob");
```

`Clippy` consomme 1 energie et affiche une attaque de 0 degat.

```cpp
bob.takeDamage(0);
```

`Bob` recoit 0 degat : ses points de vie restent a 10.

```cpp
clippy.takeDamage(5);
clippy.beRepaired(3);
```

`Clippy` passe de 10 a 5 HP, puis remonte a 8 HP. La reparation consomme 1 energie.

```cpp
clippy.takeDamage(10);
```

Comme 10 degats sont superieurs a ses 8 HP, `Clippy` tombe a 0 HP.

```cpp
clippy.attack("Bob");
clippy.beRepaired(5);
```

Les deux actions sont refusees car un robot detruit ne peut plus attaquer ni se reparer.

### Detail a noter

`ex00/ClapTrap.cpp` contient deux fois `#include "ClapTrap.hpp"`. Les include guards rendent cela sans consequence, mais une seule inclusion suffit et serait plus propre.

## 4. Exercice 01 : heritage avec ScavTrap

### Principe de l'heritage

```cpp
class ScavTrap : public ClapTrap
```

`ScavTrap` est une classe fille de `ClapTrap`.

Elle herite des attributs et des methodes de `ClapTrap`, puis ajoute ou redefinit certains comportements.

Les statistiques de `ScavTrap` sont :

| Statistique | Valeur |
| --- | ---: |
| Points de vie | 100 |
| Energie | 50 |
| Degats | 20 |

### Construction d'un ScavTrap

```cpp
ScavTrap::ScavTrap(const std::string& name) : ClapTrap(name)
```

La partie `ClapTrap(name)` construit d'abord la classe de base. Ensuite, le constructeur de `ScavTrap` remplace les statistiques par celles de `ScavTrap`.

L'ordre est donc :

1. constructeur `ClapTrap` ;
2. initialisation des valeurs de `ScavTrap` ;
3. corps du constructeur `ScavTrap`.

Le constructeur de copie utilise egalement :

```cpp
ScavTrap::ScavTrap(const ScavTrap& other) : ClapTrap(other)
```

Cela copie d'abord la partie `ClapTrap` de l'objet.

### Redefinition de `attack`

`ScavTrap` redefinit `attack` pour afficher `ScavTrap` et utiliser ses propres statistiques. La logique reste la meme :

- un robot detruit ne peut pas attaquer ;
- une attaque consomme 1 energie ;
- l'attaque affiche 20 degats.

C'est un exemple de **redefinition de methode** : la classe fille fournit sa propre version d'une methode deja presente dans la classe mere.

### Methode `guardGate`

```cpp
void ScavTrap::guardGate()
```

Cette methode affiche que le robot passe en mode gardien de porte. Elle est specifique a `ScavTrap` et n'existe pas dans `ClapTrap`.

### Scenario de `main.cpp`

```cpp
ScavTrap a("Alice");
ScavTrap b(a);
ScavTrap c("Charlie");
c = a;
```

Ce code teste :

- le constructeur avec un nom pour `a` ;
- le constructeur de copie pour `b` ;
- l'operateur d'affectation pour copier `a` dans `c`.

Puis `a` :

1. attaque `Bob`, en consommant 1 energie ;
2. perd 10 HP ;
3. recupere 5 HP, en consommant 1 energie ;
4. active le mode `guardGate`.

## 5. Exercice 02 : heritage avec FragTrap

`FragTrap` est une autre classe fille de `ClapTrap` :

```cpp
class FragTrap : public ClapTrap
```

Elle utilise les memes attributs de base, mais possede ses propres statistiques et une action speciale.

Ses statistiques sont :

| Statistique | Valeur |
| --- | ---: |
| Points de vie | 100 |
| Energie | 100 |
| Degats | 30 |

### Construction

Comme pour `ScavTrap`, les constructeurs commencent par construire la partie `ClapTrap` :

```cpp
FragTrap::FragTrap(const std::string& name) : ClapTrap(name)
```

Puis ils changent les valeurs pour obtenir les statistiques de `FragTrap`.

Le constructeur de copie :

```cpp
FragTrap::FragTrap(const FragTrap& other) : ClapTrap(other)
```

copie la partie heritee avant de terminer la construction de `FragTrap`.

### Redefinition de `attack`

`FragTrap` fournit sa propre version de `attack`. Elle reprend les memes controles et consomme 1 energie, mais l'attaque affiche 30 points de degats.

### Methode `highFivesGuys`

```cpp
void FragTrap::highFivesGuys(void)
```

Cette methode affiche une demande de high five. Elle ne modifie ni les HP ni l'energie.

### Scenario de `main.cpp`

```cpp
FragTrap a("Alice");
FragTrap b(a);
FragTrap c("Charlie");
c = a;
```

Comme dans `ex01`, le code teste le constructeur normal, le constructeur de copie et l'operateur d'affectation.

Ensuite `a` :

1. attaque `Bob` et consomme 1 energie ;
2. prend 40 degats et passe de 100 a 60 HP ;
3. se repare de 15 HP et passe a 75 HP, en consommant 1 energie ;
4. demande un high five.

## 6. Constructeurs et destructeurs avec heritage

Pour un objet `ScavTrap` ou `FragTrap`, la destruction se fait dans l'ordre inverse de la construction.

Exemple pour `FragTrap` :

1. constructeur `ClapTrap` ;
2. constructeur `FragTrap` ;
3. destructeur `FragTrap` ;
4. destructeur `ClapTrap`.

Cela explique pourquoi les messages de destruction de la classe fille apparaissent avant ceux de la classe mere.

Le mot-cle `virtual` sur le destructeur de `ClapTrap` garantit un comportement correct avec le polymorphisme.

## 7. Les Makefiles

Chaque dossier possede un Makefile presque identique.

### Variables principales

```make
NAME = claptrap
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
```

- `NAME` est le nom de l'executable.
- `CXX` est le compilateur C++.
- `-Wall` active beaucoup d'avertissements.
- `-Wextra` active des avertissements supplementaires.
- `-Werror` transforme les avertissements en erreurs.
- `-std=c++98` impose la norme C++98 demandee par le projet.

### Compilation des fichiers

```make
SRCS = main.cpp ClapTrap.cpp
OBJS = $(SRCS:.cpp=.o)
```

`OBJS` transforme chaque fichier `.cpp` en fichier objet `.o`.

La regle :

```make
%.o: %.cpp ClapTrap.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
```

compile un fichier source en fichier objet. Le fichier objet permet d'eviter de tout recompiler lorsqu'un seul fichier change.

### Regles disponibles

- `make` ou `make all` : compile l'executable.
- `make clean` : supprime les fichiers `.o`.
- `make fclean` : supprime les fichiers `.o` et l'executable.
- `make re` : nettoie puis recompile depuis zero.

La ligne :

```make
.PHONY: all clean fclean re
```

indique que ces noms sont des commandes et non des fichiers a produire.

## 8. Compiler et executer

Depuis la racine du projet :

```bash
cd ex00
make
./claptrap
make fclean
```

Pour les autres exercices :

```bash
cd ../ex01
make
./scavtrap
make fclean

cd ../ex02
make
./fragtrap
make fclean
```

Pour recompiler completement un exercice :

```bash
make re
```

## 9. Vue d'ensemble

L'evolution du projet est progressive :

```text
ClapTrap
  |
  +-- ScavTrap : 100 HP, 50 energie, 20 degats, guardGate()
  |
  +-- FragTrap : 100 HP, 100 energie, 30 degats, highFivesGuys()
```

Le projet met principalement en pratique :

- les classes et les objets ;
- l'encapsulation ;
- les constructeurs et destructeurs ;
- le constructeur de copie ;
- l'operateur d'affectation ;
- l'heritage public ;
- la redefinition de methodes ;
- les destructeurs virtuels ;
- la compilation avec un Makefile ;
- la gestion simple d'un etat avec les HP et l'energie.

## 10. Ce qu'il faut retenir de chaque exercice

Cette partie explique les nouvelles notions a apprendre, et pas seulement ce que fait le programme.

### Exercice 00 : construire une vraie classe C++

Le premier exercice sert a apprendre la base de la programmation orientee objet en C++.

#### 1. Une classe regroupe des donnees et des fonctions

Dans `ClapTrap`, les donnees sont les attributs :

```cpp
std::string _name;
unsigned int _hitPoints;
unsigned int _energyPoints;
unsigned int _attackDamage;
```

Les fonctions qui travaillent sur ces donnees sont les methodes : `attack`, `takeDamage` et `beRepaired`.

L'interet est de reunir l'etat et les actions d'un meme objet. Au lieu d'avoir plusieurs variables separees dans `main`, chaque robot sait lui-meme comment attaquer, subir des degats et se reparer.

#### 2. `private` protege l'interieur de l'objet

Dans `ex00`, les attributs sont `private`. Ce code est donc interdit depuis `main` :

```cpp
ClapTrap robot("Alice");
robot._hitPoints = 100; // interdit
```

On doit passer par les methodes publiques. C'est l'encapsulation : l'objet controle les changements qui le concernent. Par exemple, `takeDamage` empeche les HP de devenir negatifs et `attack` empeche une attaque sans energie.

#### 3. Le header et le fichier source n'ont pas le meme role

Le `.hpp` annonce l'interface publique de la classe. Le `.cpp` contient le fonctionnement detaille.

```cpp
// Dans ClapTrap.hpp : declaration
void attack(const std::string& target);

// Dans ClapTrap.cpp : definition
void ClapTrap::attack(const std::string& target)
{
  // code execute
}
```

`ClapTrap::attack` signifie que la fonction `attack` appartient a la classe `ClapTrap`. Le `::` est l'operateur de resolution de portee.

#### 4. Comprendre les constructeurs

Un constructeur est appele automatiquement quand un objet est cree. La liste d'initialisation est la bonne maniere d'initialiser les attributs :

```cpp
ClapTrap::ClapTrap(const std::string& name)
  : _name(name), _hitPoints(10), _energyPoints(10), _attackDamage(0)
```

Les attributs sont initialises avant le corps du constructeur. Ce n'est pas exactement la meme chose que leur attribuer une valeur dans le corps : l'initialisation construit directement les membres avec leur valeur finale.

#### 5. Comprendre les deux formes de copie

Le constructeur de copie cree un nouvel objet :

```cpp
ClapTrap a("Alice");
ClapTrap b(a); // construction de b a partir de a
```

L'operateur d'affectation travaille avec deux objets qui existent deja :

```cpp
ClapTrap a("Alice");
ClapTrap b("Bob");
b = a; // copie l'etat de a dans b
```

Il faut savoir les distinguer :

- `ClapTrap b(a)` appelle le constructeur de copie ;
- `b = a` appelle `operator=`.

Le `return *this` de l'operateur retourne l'objet courant. Le mot `this` est un pointeur vers l'objet sur lequel la methode est appelee. Ainsi, `this->_name` designe le nom de l'objet courant.

#### 6. Pourquoi utiliser `const std::string&` ?

Dans `attack(const std::string& target)`, le parametre est passe par reference constante :

- `&` evite de copier la chaine ;
- `const` interdit a la methode de modifier la chaine recue.

C'est une forme classique et efficace pour passer un objet qu'une fonction doit seulement lire.

#### 7. Comprendre l'etat et les conditions

Une attaque ne fait pas directement perdre des HP a la cible. Elle consomme seulement de l'energie et affiche les degats. C'est pourquoi le programme doit appeler separement `takeDamage` sur la cible.

Les tests contre zero sont importants. Les valeurs sont des `unsigned int`, donc elles ne peuvent pas etre negatives. Le code met donc les HP a zero quand les degats sont suffisants, au lieu de faire une soustraction qui pourrait provoquer un depassement.

**Ce que tu dois savoir refaire apres ex00 :** creer une classe, proteger ses attributs, initialiser ses membres, implementer les quatre fonctions speciales et gerer un etat avec des conditions.

### Exercice 01 : apprendre l'heritage avec `ScavTrap`

Le deuxieme exercice repond a une question : comment creer un nouveau type de robot qui reutilise le code de `ClapTrap` ?

#### 1. Une classe fille reutilise une classe mere

```cpp
class ScavTrap : public ClapTrap
```

Cela signifie qu'un `ScavTrap` est aussi un `ClapTrap`, mais avec des caracteristiques supplementaires. Il reutilise `takeDamage` et `beRepaired`, et possede en plus `guardGate`.

L'heritage evite de recopier toute la logique commune dans `ScavTrap.cpp`.

#### 2. Pourquoi les attributs deviennent `protected`

En `ex00`, les attributs sont `private`, donc seule la classe `ClapTrap` peut y acceder. En `ex01`, ils deviennent `protected` :

```cpp
protected:
  unsigned int _hitPoints;
```

`ScavTrap` peut alors modifier ses statistiques. En revanche, du code externe comme `main.cpp` ne peut toujours pas acceder directement a ces attributs.

Resume des niveaux d'acces :

- `private` : accessible uniquement dans la classe qui declare le membre ;
- `protected` : accessible dans la classe et ses classes filles ;
- `public` : accessible depuis l'exterieur.

#### 3. Construire la classe mere avant la classe fille

```cpp
ScavTrap::ScavTrap(const std::string& name) : ClapTrap(name)
```

`ClapTrap(name)` appelle le constructeur de la classe mere. La construction se fait toujours dans cet ordre :

1. construction de la partie `ClapTrap` ;
2. initialisation des membres propres a `ScavTrap` ;
3. execution du corps du constructeur `ScavTrap`.

Ici, `ClapTrap` donne d'abord un nom et des valeurs de base, puis `ScavTrap` remplace les statistiques par 100 HP, 50 energie et 20 degats.

#### 4. Redefinir `attack`

`ScavTrap` possede une methode `attack` avec la meme signature que celle de `ClapTrap`. La version appelee depend du type de l'objet : un `ScavTrap` utilise son attaque a 20 degats.

Ce n'est pas une nouvelle surcharge. Une surcharge aurait un nom identique mais des parametres differents. Ici, c'est une redefinition : meme nom, meme parametres, comportement specialise.

#### 5. Copier la partie mere

```cpp
ScavTrap::ScavTrap(const ScavTrap& other) : ClapTrap(other)
```

La partie `ClapTrap` de `other` est copiee par le constructeur de copie de la classe mere. De la meme maniere, `ClapTrap::operator=(other)` dans l'operateur d'affectation de `ScavTrap` reutilise la copie deja ecrite dans `ClapTrap`.

**Ce que tu dois savoir refaire apres ex01 :** creer une classe fille, appeler le constructeur de la classe mere, choisir `private/protected/public`, redefinir une methode et reutiliser l'operateur de copie de la classe mere.

### Exercice 02 : plusieurs classes filles et polymorphisme

`FragTrap` est une deuxieme classe fille independante :

```text
      ClapTrap
      /      \\
   ScavTrap  FragTrap
```

`ScavTrap` et `FragTrap` partagent le code de `ClapTrap`, mais ne s'heritent pas l'une de l'autre.

#### 1. Meme base, statistiques differentes

`FragTrap` reutilise les methodes communes, mais configure ses propres valeurs : 100 HP, 100 energie et 30 degats. Le principe est celui d'une famille de classes : les donnees et actions communes sont dans la base, les differences sont dans les classes filles.

#### 2. Ajouter une capacite propre

```cpp
void highFivesGuys(void);
```

Cette methode n'existe que dans `FragTrap`. Un `ClapTrap` ou un `ScavTrap` ne peut pas l'appeler, car ils ne possedent pas cette capacite.

#### 3. Pourquoi le destructeur de `ClapTrap` est `virtual`

Dans `ex01` et `ex02`, le destructeur de la classe mere est declare ainsi :

```cpp
virtual ~ClapTrap();
```

Cela est necessaire si on detruit un objet fille a travers un pointeur de type mere :

```cpp
ClapTrap* robot = new FragTrap("Alice");
delete robot;
```

Avec un destructeur virtuel, `delete` appelle d'abord `~FragTrap`, puis `~ClapTrap`. Sans `virtual`, le destructeur de la fille pourrait ne pas etre appele correctement.

#### 4. La notion de polymorphisme

Le polymorphisme permet de manipuler plusieurs types d'objets par une interface commune. Par exemple, un pointeur `ClapTrap*` peut pointer vers un `ScavTrap` ou un `FragTrap`.

Pour que l'appel a `attack` choisisse la version de la classe fille via un pointeur de base, la methode doit aussi etre declaree `virtual` dans la classe mere. Dans ton code actuel, le destructeur est virtuel, mais `attack` ne l'est pas. Le projet montre donc deja la preparation au polymorphisme, sans utiliser encore tout son comportement dynamique.

**Ce que tu dois savoir refaire apres ex02 :** construire plusieurs classes filles a partir d'une base commune, factoriser le code partage, ajouter des comportements specifiques et comprendre le role du destructeur virtuel.

## 11. Ordre de vie d'un objet herite

Avec :

```cpp
FragTrap a("Alice");
```

les messages apparaissent dans cet ordre pendant la construction :

1. `ClapTrap` construit sa partie ;
2. `FragTrap` termine la construction.

A la fin du scope, l'ordre est inverse :

1. `FragTrap` est detruit ;
2. `ClapTrap` est detruit.

Cet ordre garantit que la classe fille termine son travail avant que sa partie mere ne disparaisse.

## 12. Comment lire un exercice de ce type

Quand tu rencontres une nouvelle classe, pose-toi toujours ces questions :

1. Quels sont ses attributs et qui a le droit de les modifier ?
2. Quels constructeurs existent et quelles valeurs sont initialisees ?
3. La classe herite-t-elle d'une autre classe ?
4. Quelles methodes sont communes et lesquelles sont specialisees ?
5. Que se passe-t-il si l'objet est copie, affecte, detruit ou utilise sans energie ?
6. Quel est l'ordre des constructeurs et destructeurs ?

Si tu sais repondre a ces questions, tu comprends l'essentiel de CPP03 et tu es pret pour les exercices suivants sur l'heritage et le polymorphisme.
