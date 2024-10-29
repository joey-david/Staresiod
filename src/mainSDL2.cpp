#include "affichageSDL2.h"
#include "Menu.h"

int main (int argc, char** argv) {
	const std::string options[] = {"ENDLESS", "MULTIPLAYER"};
    Menu m(options, 2);
	m.menuBoucle();
	if(!m.multijoueur) {
		SDLSimple sj;
		sj.sdlBoucle();
	} else {
		SDLMulti sj;
		sj.sdlBoucleMulti();
	}

	return 0;
}


