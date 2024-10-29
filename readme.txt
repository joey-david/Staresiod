12115771 DAVID Joey
12020982 POUPON Ugo
lien vers la forge : https://forge.univ-lyon1.fr/p2020982/projet.git

	STARESIOD - MINI-JEU DEVELOPPE DANS LE CADRE DE L'UE LIFAPCD
	

	--> Principe de base
	 
Staresiod est un jeu de survie, où un joeur contrôle un vaisseau dans un champ d'astéroïdes. Le but
pour le joueur est de rester en vie le plus longtemps possible tout en détruisant des astéroïdes, afin
de maximiser son score. Pour ce faire, le joueur peut se déplacer sur l'écran et tirer des projectiles,
qui détruiront les astéroïdes de taille variable en un certain nombre d'impact.

	--> Contrôles

z : avancer
q : tourner à gauche
d : tourner à droite
s : freiner/reculer
v : tirer un projectile

	--> Power-ups
	
Des power-ups apparaissent régulièrement sur le terrain. Pour activer un power-up, le joueur doit faire
rentrer en contact le vaisseau et le power-up. Il y a 4 types de power-ups, qui ont respectivement les
fonctionnalités suivantes.
(1): Destruction instantanée de tous les astéroïdes se trouvant sur le terrain à l'instant du ramassage
du power-up.
(2): Affectation temporaire d'un mode "perceuse" aux projectiles du vaisseau, qui deviennent
indestructibles et détruisent tout ce avec quoi ils entrent en contact.
(3): Affection temporaire d'un mode "indestructible" au vaisseau, qui peut donc détruire les astéroïdes
en les touchant pendant l'intervalle d'activation du power-up.
(4): Affectation temporaire d'un mode "vitesse" au vaisseau, qui devient deux fois plus rapide sur
pendant l'intervalle d'activation du power-up.

	--> Mode multijoueur

Lors de la sélection du mode de jeu dans le menu, il est possible de choisir le mode multi-joueur. Un
mode compétitif se lance, où deux vaisseaux doivent atteindre un plus haut score que l'adversaire. Dans
ce cas, les contrôles du second vaisseau (rose) sont :
o : avancer
k : tourner à gauche
l : tourner à droite
m : freiner/reculer
p : tirer un projectile


__________________________________________________________________________________________________


	--> Compilation/execution

Les exécutables peuvent être générés ou mis à jour avec la commande make. Il y a trois fonctionnalités
principales dans cette archive, chacune implémentée en un exécutable:

bin/jeuSDL: Lancement du jeu avec un affichage SDL.

bin/jeuTexte : Lancement du jeu avec un affichage texte (fonctionnalités réduites).

bin/test : Exécution de tests de régression de toutes les classes principales du Jeu.

__________________________________________________________________________________________________

	
	--> Organisation du repértoire racine

bin/ : contient les exécutables.

data/ : contient les assets nécessaires à l'éxecution en mode SDL du jeu : sprites, textures,
animations, etc. On y trouve aussi le fichier highscore.txt, où est conservé et mis à jour le plus haut
score obtenu sur le jeu.

doc/ : contient la documentation doxygen du jeu dans doc/html, le diagramme des classes UML, le
diagramme de Gantt et la présentation orale pour la soutenance.

obj/ : contient les fichiers objets nécessaires à la fabrication des fichiers exécutables.

src/ : contient le code du jeu. Fichiers .h et .cpp.

le repértoire racine contient aussi un makefile, ainsi que ce fichier readme.
