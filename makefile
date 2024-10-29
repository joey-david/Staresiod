all: bin/test bin/jeuTexte bin/jeuSDL

#partie SDL2
bin/jeuSDL: obj/mainSDL2.o obj/Menu.o obj/affichageSDL2.o obj/Jeu.o obj/JeuMulti.o obj/Vaisseau.o obj/Vec2.o obj/Objet.o obj/Terrain.o obj/PowerUp.o
	g++ -g -o bin/jeuSDL obj/mainSDL2.o obj/Menu.o obj/affichageSDL2.o obj/Jeu.o obj/JeuMulti.o obj/Vaisseau.o obj/Vec2.o obj/Objet.o obj/Terrain.o obj/PowerUp.o -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer

obj/Menu.o: src/Menu.h src/Menu.cpp
	g++ -g -Wall -c src/Menu.cpp -o obj/Menu.o

obj/mainSDL2.o: src/affichageSDL2.h src/mainSDL2.cpp
	g++ -g -Wall -c src/mainSDL2.cpp -o obj/mainSDL2.o

obj/affichageSDL2.o: src/affichageSDL2.h src/affichageSDL2.cpp src/JeuMulti.h src/Jeu.h
	g++ -g -Wall -c src/affichageSDL2.cpp -o obj/affichageSDL2.o

obj/JeuMulti.o: src/JeuMulti.h src/JeuMulti.cpp src/Vaisseau.h src/Terrain.h src/PowerUp.h
	g++ -g -Wall -c src/JeuMulti.cpp -o obj/JeuMulti.o

#partie Texte
bin/jeuTexte : obj/mainTexte.o obj/txtJeu.o obj/JeuEnTxt.o obj/Vaisseau.o obj/Vec2.o obj/Objet.o obj/Terrain.o obj/winTxt.o obj/PowerUp.o
	g++ -g -o bin/jeuTexte obj/mainTexte.o obj/txtJeu.o obj/JeuEnTxt.o obj/Vaisseau.o obj/Vec2.o obj/Objet.o obj/Terrain.o obj/winTxt.o obj/PowerUp.o

obj/winTxt.o: src/winTxt.h src/winTxt.cpp
	g++ -g -Wall -c src/winTxt.cpp -o obj/winTxt.o

obj/mainTexte.o: src/txtJeu.h src/mainTexte.cpp
	g++ -g -Wall -c src/mainTexte.cpp -o obj/mainTexte.o

obj/txtJeu.o: src/txtJeu.h src/txtJeu.cpp src/JeuEnTxt.h
	g++ -g -Wall -c src/txtJeu.cpp -o obj/txtJeu.o

obj/JeuEnTxt.o: src/JeuEnTxt.h src/JeuEnTxt.cpp src/Vaisseau.h src/Terrain.h src/PowerUp.h
	g++ -g -Wall -c src/JeuEnTxt.cpp -o obj/JeuEnTxt.o

#partie Test
bin/test: obj/mainTest.o obj/Jeu.o obj/Vaisseau.o obj/Vec2.o obj/Objet.o obj/Terrain.o obj/PowerUp.o
	g++ -g -o bin/test obj/mainTest.o obj/Jeu.o obj/Vaisseau.o obj/Vec2.o obj/Objet.o obj/Terrain.o obj/PowerUp.o

obj/mainTest.o: src/Vec2.h src/mainTest.cpp src/Objet.h
	g++ -g -Wall -c src/mainTest.cpp -o obj/mainTest.o

#utilisé dans plusieurs exécutables

obj/Jeu.o: src/Jeu.h src/Jeu.cpp src/Vaisseau.h src/Terrain.h src/PowerUp.h
	g++ -g -Wall -c src/Jeu.cpp -o obj/Jeu.o

obj/Terrain.o: src/Terrain.h src/Terrain.cpp
	g++ -g -Wall -c src/Terrain.cpp -o obj/Terrain.o

obj/Vaisseau.o: src/Vaisseau.h src/Vaisseau.cpp  src/Objet.h
	g++ -g -Wall -c src/Vaisseau.cpp -o obj/Vaisseau.o

obj/Objet.o: src/Objet.cpp src/Objet.h src/Vec2.h
	g++ -g -Wall -c src/Objet.cpp -o obj/Objet.o

obj/PowerUp.o: src/PowerUp.cpp src/PowerUp.h src/Vec2.h
	g++ -g -Wall -c src/PowerUp.cpp -o obj/PowerUp.o

obj/Vec2.o: src/Vec2.h  src/Vec2.cpp
	g++ -g -Wall -c src/Vec2.cpp -o obj/Vec2.o

clean:
	rm bin/* obj/* data/highscore.txt
