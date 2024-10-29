#include <iostream>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // WIN32
#include "winTxt.h"

#include "JeuEnTxt.h"

void txtAff(WinTXT & win, JeuEnTxt & jeuEnTxt) {

	const Terrain& ter = jeuEnTxt.t;
	const Vaisseau& vaiss = jeuEnTxt.v;

/////////////////

	win.clear();

    // Affichage des murs et des pastilles
	for(int x=0;x/2<ter.getDimX();++x)
		for(int y=0;y<ter.getDimY();++y)
			win.print( x, y, '.');

    // Affichage du Vaisseau
	if (sin(vaiss.getPosAngObj())>=sqrt(2.0)/2.0){
		win.print(vaiss.getPosObj().getX(),vaiss.getPosObj().getY(),'V');
	}
	else if (cos(vaiss.getPosAngObj())>=sqrt(2.0)/2.0){
		win.print(vaiss.getPosObj().getX(),vaiss.getPosObj().getY(),'>');
	}
	else if (cos(vaiss.getPosAngObj())<-1.0*sqrt(2.0)/2.0){
		win.print(vaiss.getPosObj().getX(),vaiss.getPosObj().getY(),'<');
	}
	else if (sin(vaiss.getPosAngObj())<-1.0*sqrt(2.0)/2.0){
		win.print(vaiss.getPosObj().getX(),vaiss.getPosObj().getY(),'A');
	}
	else assert(1==2);

	// Affichage des Asteroides
	for (int i = 0; i<(int)jeuEnTxt.asteroides.size(); i++){
		win.print(jeuEnTxt.asteroides[i].getPos().getX(),jeuEnTxt.asteroides[i].getPos().getY(),'Q');
	}

	for (int i = 0; i< (int)vaiss.projectiles.size(); i++){
		win.print(vaiss.projectiles[i].getPos().getX(), vaiss.projectiles[i].getPos().getY(), 'o');
	}
	win.draw();
}

void txtBoucle (JeuEnTxt & jeuEnTxt) {
	// Creation d'une nouvelle fenetre en mode texte
	// => fenetre de dimension et position (WIDTH,HEIGHT,STARTX,STARTY)

    WinTXT win (jeuEnTxt.t.getDimX(),jeuEnTxt.t.getDimY());

/////////////////////////////

	bool ok = true;
	int c;

	do {
	    txtAff(win,jeuEnTxt);
        #ifdef _WIN32
        Sleep(100);
		#else
		usleep(10000);
        #endif // WIN32

		jeuEnTxt.update();
		cout << jeuEnTxt.asteroides.size() << endl << endl;
		cout << jeuEnTxt.v.getPVObj() << endl;
		//debug: pos et vitesse des astéroïdes
    	int i;
		c = win.getCh();
		switch (c) {
			case 'z':
				jeuEnTxt.actionClavier('z');
				break;
			case 's':
				jeuEnTxt.actionClavier('s');
				break;
			case 'q':
				jeuEnTxt.actionClavier('q');
				break;
			case 'd':
				jeuEnTxt.actionClavier('d');
				break;
			case 'v':
				jeuEnTxt.actionClavier('v');
				break;
			case 'p':
				ok = false;
				break;
		}
		if (jeuEnTxt.v.getPVObj()<=0)
			ok = false;
	} while (ok);

}

