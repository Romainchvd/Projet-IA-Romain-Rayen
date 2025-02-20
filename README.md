# PROJET_IA - Romain & Rayen

# SOMMAIRE
# 1. Introduction
# 2. Concept du Jeu
# 3. Game Design
# 4. Graphismes et Direction Artistique
# 6. Gestion de Projet et Planning
# 7. Conclusion et Perspectives

# Introduction
Le projet est une démonstration de trois gestions différentes de l'IA dans un jeu vidéo. Il est réalisé dans le cadre de la prédagogie par Projet au Gaming Campus pour la classe GTECH 1.
Il n'est pas destinée à la commercialisation et n'est pas un vrai jeu mais un exercice destiné à augmenter les compétences des étudiants dans les différents algorithmes.
Le projet est codé en C++ 14 et utilise la bibliothèque SFML. Il est livré avec le présent document. La gestion du code s'est effectuée avec GitHub et Visual Studio. Le projet est découpé en
plusieurs fichiers (cpp et hpp) dans un but de clareté, de lisibilité et de practicité.

# Concept du jeu

Le "jeu" se déroule dans un espace représenté sous forme de grille dans une fenêtre de taille 800x600. Il se joue uniquement au clavier et à pour but de montrer des comportements basiques
d'ennemis en utilisant un Behavior Tree, une FSM et un GOAP. Le jeu n'utilise pas l'algorithme A* et utilise un système de waypoints pour le déplacement des ennemis lorsqu'ils ne détectent
pas le joueur. Le joueur se déplace ) l'aide de ZQSD. Il est possible de désactiver les ennemis et d'intéragir avec eux (ce dernier point est expliqué ci-après).

# Game design

Les 4 personnages du jeu sont représentés sous forme de carrés (RectangleShape) et sont de différentes couleurs.
Le joueur est de couleur bleue.
L'ennemi utilisant le behavior tree est de couleur verte. (désigné BTEnemy ci-après)
L'ennemi utilisant la FSM est de couleur rouge. (désigné FSMEnemy ci-après)
L'ennemi utilisant le GOAP est de couleur magenta. (désigné GOAPEnemy ci-après)

Le BTEnemy possède deux actions: il patrouille tant qu'il ne détecte pas le joueur. Le rayon de détection du joueur est d'un périmètre de 100 pixels autour du joueur. Lorsqu'il touche le 
joueur, le joueur change de couleur pour du Cyan. Lorsqu'il perd de vue le joueur, il retourne patrouiller. Il patrouille en ligne droite selon deux points et s'il rencontre un mur pendant
sa patrouille, il se crashe et revient au bout de 5 secondes.

Le FSMEnemy possède trois actions: sa patrouille est similaire à celle du BTEnemy, à la différence qu'elle s'effectue suivant un rectangle. Lorsqu'il détecte le joueur, il adopte le même 
comportement que le BTEnemy. Lorsqu'il perd le joueur de vue, il reste quelques instants dans la zone. S'il ne détecte pas l'ennemi, il retourne à sa patrouille. S'il rencontre un mur 
pendant sa phase de recherche (celle qui suit la poursuite), il retourne à sa patrouille. Il ne dispose pas de colisions et ne se crashe pas lorsqu'il rencontre un mur, pouvant les 
traverser (ce point est abordé à la fin du présent document), uniquement durant la phase de patrouille.

Le GOAPEnemy possède deux actions: sa patrouille est similaire à celle du BTEnemy. Sa deuxième action est la fuite: s'il détecte le joueur, il fera tout pour le fuir. Si le joueur le 
touche, le GOAPEnemy devient blanc. Lorsqu'il arrive dans un périmètre de 120 pixels autour du joueur, il retourne patrouiller. Il possède les mêmes problèmes de colisions lors de sa 
patrouille que les autres ennemis.

Touches concernant les ennemis:
F désactive ou réactive le FSMEnemy
G désactive ou réactive le GOAPEnemy
B désactive ou réactive le BTEnemy

# Graphismes et direction artistique

Le projet étant avant tout une démonstration technique, il n'utilise aucune texture et utilise le rendu natif de SFML. L'intégralité du projet est sous forme de carrés.

# Gestion de projet et planning

La répartition des rôles s'est effectuée comme suit:
Romain : Documentation, PowerPoint, behavior tree, GOAP, Structure du code
Rayen: FSM(1)

1 : Rayen a codé le FSM en étant largement aidé de Romain du fait de difficultés. Une version du FSM intégralement codé par Rayen a été abandonnée car elle ne fonctionnait pas.

Le planning se présente ainsi:

Vendredi: Fichiers du BT et initialisation du projet (tenu)
Samedi & dimanche : prototype d'un algorithme (tenu)
Lundi: finalisation du behavior tree (tenu)
Mardi: FSM (tenu)
Mercredi: GOAP (tenu)
Jeudi: Fonctionnalités supplémentaires et bugs (tenu, à l'exception du problème de patrouille)
Vendredi: Nettoyage du code et commentaires (tenu en avance, jeudi) & soutenance

# Conclusion et perspectives

Le projet respecte le cahier des charges demandé et le planning a pu être respecté. Cependant, le problème non résolu de patrouille du fait de l'absence d'un 4e algorithme A*
(non prévu initialement et écarté en fin de projet pour ne pas risquer de rendre caduque tous les déplacements dans le jeu et les méthodes liées) est une grande frustration. Le projet 
aurait pu gagner en complexité et être entièrement débugué avec une meilleure répartition des tâches, du fait de problèmes du côté de Rayen et d'une perte de motivation de son côté.
Le projet a cependant permis de comprendre mieux le fonctionnement des 3 algorithmes utilisés et les compétences acquises faciliteront l'apprentissage des moteurs de jeu dans le champ de 
l'IA. Le planning initial a été tenu bien qu'il n'était pas aussi ambitieux qu'il aurait pû l'être avec une meilleure répartition des tâches. Une mise à jour en dehors du cadre scolaire
peut être envisagée afin d'implémenter l'algorithme A*.
