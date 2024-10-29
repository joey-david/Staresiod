#include "affichageSDL2.h"

const int FPS = 30;
const int FRAME_TIME = 1000 / FPS;

int timer = SDL_GetTicks();
float temps () {
    return float(SDL_GetTicks()) / CLOCKS_PER_SEC;  // conversion des ms en secondes en divisant par 1000
}

// ============= CLASS IMAGE =============== //

Image::Image () : m_surface(nullptr), m_texture(nullptr), m_hasChanged(false) {
}

Image::~Image()
{
    SDL_FreeSurface(m_surface);
    SDL_DestroyTexture(m_texture);

    m_surface = nullptr;
    m_texture = nullptr;
    m_hasChanged = false;
}

void Image::loadFromFile (const char* filename, SDL_Renderer * renderer) {
    m_surface = IMG_Load(filename);
    if (m_surface == nullptr) {
        string nfn = string("../") + filename;
        cout << "Error: cannot load "<< filename <<". Trying "<<nfn<<endl;
        m_surface = IMG_Load(nfn.c_str());
        if (m_surface == nullptr) {
            nfn = string("../") + nfn;
            m_surface = IMG_Load(nfn.c_str());
        }
    }
    if (m_surface == nullptr) {
        cout<<"Error: cannot load "<< filename <<endl;
        SDL_Quit();
        exit(1);
    }

    SDL_Surface * surfaceCorrectPixelFormat = SDL_ConvertSurfaceFormat(m_surface,
        SDL_PIXELFORMAT_ARGB8888,0);
    SDL_FreeSurface(m_surface);
    m_surface = surfaceCorrectPixelFormat;

    m_texture = SDL_CreateTextureFromSurface(renderer,surfaceCorrectPixelFormat);
    if (m_texture == NULL) {
        cout << "Error: problem to create the texture of "<< filename<< endl;
        SDL_Quit();
        exit(1);
    }
}

void Image::loadFromCurrentSurface (SDL_Renderer * renderer) {
    m_texture = SDL_CreateTextureFromSurface(renderer,m_surface);
    if (m_texture == nullptr) {
        cout << "Error: problem to create the texture from surface " << endl;
        SDL_Quit();
        exit(1);
    }
}

void Image::draw (SDL_Renderer * renderer, int x, int y, int w, int h, double angle) {
    int ok;
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = (w<0)?m_surface->w:w;
    r.h = (h<0)?m_surface->h:h;

    if (m_hasChanged) {
        ok = SDL_UpdateTexture(m_texture,nullptr,m_surface->pixels,m_surface->pitch);
        assert(ok == 0);
        m_hasChanged = false;
    }

    ok = SDL_RenderCopyEx(renderer,m_texture,nullptr,&r,angle,nullptr,SDL_FLIP_NONE);
    assert(ok == 0);
}


SDL_Texture * Image::getTexture() const {return m_texture;}

void Image::setSurface(SDL_Surface * surf) {m_surface = surf;}




// ============= CLASS SDLJEU =============== //

SDLSimple::SDLSimple () : jeu() {
    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Erreur lors de l'initialisation de la SDL : " << 
            SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    if (TTF_Init() != 0) {
        cout << "Erreur lors de l'initialisation de la SDL_ttf : " << 
            TTF_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if( !(IMG_Init(imgFlags) & imgFlags)) {
        cout << "SDL_image could not initialize! SDL_image Error: " << 
            IMG_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    // if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    // {
    //     cout << "SDL_mixer could not initialize! SDL_mixer Error: " << 
    //         Mix_GetError() << endl;
    //     cout << "No sound !!!" << endl;
    //     //SDL_Quit();exit(1);
    //     withSound = false;
    // }
    // else withSound = true;

	int dimx, dimy;
	dimx = jeu.t.getDimX();
	dimy = jeu.t.getDimY();

    // Creation de la fenetre
    window = SDL_CreateWindow("Staresiod", SDL_WINDOWPOS_CENTERED, 
    SDL_WINDOWPOS_CENTERED, dimx, dimy, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == nullptr) {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() 
        << endl; 
        SDL_Quit(); 
        exit(1);
    }

    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    // IMAGES
    im_background.loadFromFile("data/background.png",renderer);
    im_vaisseau.loadFromFile("data/ship.png",renderer);
    im_vaissAcc1.loadFromFile("data/shipacc1.png",renderer);
    im_vaissAcc2.loadFromFile("data/shipacc2.png",renderer);
    im_vaissBra1.loadFromFile("data/shipbrak1.png",renderer);
    im_vaissBra2.loadFromFile("data/shipbrak2.png",renderer);
    im_projectile.loadFromFile("data/laser.png",renderer);
    im_asteroide1.loadFromFile("data/asteroide1.png",renderer);
    im_asteroide2.loadFromFile("data/asteroide2.png",renderer);
    im_asteroide3.loadFromFile("data/asteroide3.png",renderer);
    im_asteroide4.loadFromFile("data/asteroide4.png",renderer);
    im_asteroide5.loadFromFile("data/asteroide5.png",renderer);
    im_powerup_t1.loadFromFile("data/powerUp_explosion.png",renderer);
    im_powerup_t2.loadFromFile("data/powerUp_invulnerability.png",renderer);
    im_powerup_t3.loadFromFile("data/powerUp_speed.png",renderer);
    im_powerup_t4.loadFromFile("data/powerUp_drill.png",renderer);

    // FONTS
    font = TTF_OpenFont("data/DejaVuSansCondensed.ttf",50);
    if (font == nullptr)
        font = TTF_OpenFont("../data/DejaVuSansCondensed.ttf",50);
    if (font == nullptr) {
            cout << "Failed to load DejaVuSansCondensed.ttf! SDL_TTF Error: "
            << TTF_GetError() << endl; 
            SDL_Quit(); 
            exit(1);
	}
	font_color.r = 50;font_color.g = 50;font_color.b = 255;


    // SONS
    // if (withSound)
    // {
    //     sound = Mix_LoadWAV("data/son.wav");
    //     if (sound == nullptr) 
    //         sound = Mix_LoadWAV("../data/son.wav");
    //     if (sound == nullptr) {
    //             cout << "Failed to load son.wav! SDL_mixer Error: " 
    //             << Mix_GetError() << endl; 
    //             SDL_Quit();
    //             exit(1);
    //     }
    // }
}

SDLSimple::~SDLSimple () {
    // if (withSound) Mix_Quit();
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

SDL_Rect* SDLSimple::createTableFrames(SDL_Renderer* renderer, SDL_Texture* spriteSheet,
    int nbCols, int nbLines, int displayScale) {
    int textureWidth, textureHeight;
    SDL_QueryTexture(spriteSheet, NULL, NULL, &textureWidth, &textureHeight);
    const int FRAME_WIDTH = textureWidth / nbCols; // Assuming equal-sized frames
    const int FRAME_HEIGHT = textureHeight / nbLines;

    // Calculate the coordinates of each frame on the sprite sheet
    int NUM_FRAMES = nbCols * nbLines;
    SDL_Rect* frames = new SDL_Rect[NUM_FRAMES];
    for (int i = 0; i < NUM_FRAMES; ++i) {
        int row = i / nbCols;
        int col = i % nbCols;
        frames[i] = { col * FRAME_WIDTH, row * FRAME_HEIGHT, FRAME_WIDTH, FRAME_HEIGHT };
    }
    return frames;
}

void SDLSimple::displayAnimFrame(SDL_Renderer* renderer, SDL_Rect* tab,
    SDL_Texture* spriteSheet, int counter, int posX, int posY, float displayScale) {
    const int FRAME_WIDTH = tab[0].w;  // Assuming equal-sized frames
    const int FRAME_HEIGHT = tab[0].h;
    const int DISPLAY_WIDTH = FRAME_WIDTH * displayScale;
    const int DISPLAY_HEIGHT = FRAME_HEIGHT * displayScale;
    SDL_Rect animationRect = { posX-DISPLAY_WIDTH/2, posY-DISPLAY_HEIGHT/2,
     DISPLAY_WIDTH, DISPLAY_HEIGHT };

    // Set the texture and source rectangle for the current frame
    SDL_RenderCopy(renderer, spriteSheet, &tab[counter], &animationRect);
}




void SDLSimple::sdlAff () {
	//Remplir l'écran de blanc
    SDL_SetRenderDrawColor(renderer, 230, 240, 255, 255);
    SDL_RenderClear(renderer);

    const PowerUp& powerup = jeu.p;
	const Vaisseau& vaiss = jeu.v;
    //Afficher le background oh yeah B)
    im_background.draw(renderer, 0, 0, jeu.t.getDimX(), 
        jeu.t.getDimY());

	// Afficher le sprite du vaisseau
    if (vaiss.indice_acc ==0) {
	im_vaisseau.draw(renderer,
        vaiss.getPosObj().getX() - vaiss.getTailleObj()/2,
        vaiss.getPosObj().getY() - vaiss.getTailleObj()/2,
        50.0,
        50.0,
        (vaiss.getPosAngObj()+M_PI/2) * 180.0 / M_PI);
    }
    else if (vaiss.indice_acc > 0 && vaiss.indice_acc < 1) {
	im_vaissAcc1.draw(renderer,
        vaiss.getPosObj().getX() - vaiss.getTailleObj()/2,
        vaiss.getPosObj().getY() - vaiss.getTailleObj()/2,
        50.0,
        50.0,
        (vaiss.getPosAngObj()+M_PI/2) * 180.0 / M_PI);
    }
    else if (vaiss.indice_acc >= 1) {
	im_vaissAcc2.draw(renderer,
        vaiss.getPosObj().getX() - vaiss.getTailleObj()/2,
        vaiss.getPosObj().getY() - vaiss.getTailleObj()/2,
        50.0,
        50.0,
        (vaiss.getPosAngObj()+M_PI/2) * 180.0 / M_PI);
    }
    else if (vaiss.indice_acc < 0 && vaiss.indice_acc >= -1) {
	im_vaissBra1.draw(renderer,
        vaiss.getPosObj().getX() - vaiss.getTailleObj()/2,
        vaiss.getPosObj().getY() - vaiss.getTailleObj()/2,
        50.0,
        50.0,
        (vaiss.getPosAngObj()+M_PI/2) * 180.0 / M_PI);
    }
    else if (vaiss.indice_acc <= -1) {
	im_vaissBra2.draw(renderer,
        vaiss.getPosObj().getX() - vaiss.getTailleObj()/2,
        vaiss.getPosObj().getY() - vaiss.getTailleObj()/2,
        50.0,
        50.0,
        (vaiss.getPosAngObj()+M_PI/2) * 180.0 / M_PI);
    }

	// Afficher les sprites des projectiles
    for (int i = 0; i<(int)vaiss.projectiles.size(); i++)
	    im_projectile.draw(renderer,
            vaiss.projectiles[i].getPos().getX() - 5/2,
            vaiss.projectiles[i].getPos().getY() - 5/2,
            8,
            3,
            vaiss.projectiles[i].getPosAng() * 180.0 / M_PI);

    //Afficher les sprites des asteroides
    for (int i = 0; i<(int)jeu.asteroides.size(); i++){
        switch(int(jeu.asteroides[i].getTaille())){
            case 20:
                im_asteroide1.draw(renderer,
                jeu.asteroides[i].getPos().getX()- jeu.asteroides[i].getTaille()/2, 
                jeu.asteroides[i].getPos().getY()- jeu.asteroides[i].getTaille()/2,
                jeu.asteroides[i].getTaille(),
                jeu.asteroides[i].getTaille(),
                jeu.asteroides[i].getPosAng()* 180.0 / M_PI);
                break;
            case 40:
                im_asteroide2.draw(renderer,
                jeu.asteroides[i].getPos().getX()- jeu.asteroides[i].getTaille()/2, 
                jeu.asteroides[i].getPos().getY()- jeu.asteroides[i].getTaille()/2,
                jeu.asteroides[i].getTaille(),
                jeu.asteroides[i].getTaille(),
                jeu.asteroides[i].getPosAng()* 180.0 / M_PI);
                break;
            case 60:
                im_asteroide3.draw(renderer,
                jeu.asteroides[i].getPos().getX()- jeu.asteroides[i].getTaille()/2, 
                jeu.asteroides[i].getPos().getY()- jeu.asteroides[i].getTaille()/2,
                jeu.asteroides[i].getTaille(),
                jeu.asteroides[i].getTaille(),
                jeu.asteroides[i].getPosAng()* 180.0 / M_PI);
                break;
            case 80:
                im_asteroide4.draw(renderer,
                jeu.asteroides[i].getPos().getX()- jeu.asteroides[i].getTaille()/2, 
                jeu.asteroides[i].getPos().getY()- jeu.asteroides[i].getTaille()/2,
                jeu.asteroides[i].getTaille(),
                jeu.asteroides[i].getTaille(),
                jeu.asteroides[i].getPosAng()* 180.0 / M_PI);
                break;
            case 100:
                im_asteroide5.draw(renderer,
                jeu.asteroides[i].getPos().getX()- jeu.asteroides[i].getTaille()/2, 
                jeu.asteroides[i].getPos().getY()- jeu.asteroides[i].getTaille()/2,
                jeu.asteroides[i].getTaille(),
                jeu.asteroides[i].getTaille(),
                jeu.asteroides[i].getPosAng()* 180.0 / M_PI);
                break;
            default:
                break;
        }
    }
    
    //Afficher le sprite du powerup
    if(powerup.getActivation()) {
        switch(powerup.getType()) {
            case 1: im_powerup_t1.draw(renderer,powerup.getPos().getX()-25,
                powerup.getPos().getY()-20,40,40);
                break;
            case 2: im_powerup_t2.draw(renderer,powerup.getPos().getX()-25,
                powerup.getPos().getY()-20,40,40);
                break;
            case 3: im_powerup_t3.draw(renderer,powerup.getPos().getX()-25,
                powerup.getPos().getY()-20,40,40);
                break;
            case 4: im_powerup_t4.draw(renderer,powerup.getPos().getX()-25,
                powerup.getPos().getY()-20,40,40);
                break;
            default: break;
    }
    }
    
    //Afficher le score
    SDL_Color couleur = {180, 180, 180};
    SDL_Surface* surfaceScore = TTF_RenderText_Solid(font, ("SCORE : " + to_string(jeu.score)).c_str(), couleur);
    SDL_Texture* textureScore = SDL_CreateTextureFromSurface(renderer, surfaceScore);
    SDL_Rect scoreRect = {25, 25, surfaceScore->w/2, surfaceScore->h/2};
    SDL_RenderCopy(renderer, textureScore, NULL, &scoreRect);
    SDL_FreeSurface(surfaceScore);
    SDL_DestroyTexture(textureScore);
}

void SDLSimple::sdlBoucle () {
    SDL_Event events;
    bool quit = false;

    SDL_Texture* spriteSheetExp = IMG_LoadTexture(renderer, "data/explosion_sheet.png");
    SDL_Rect* table_exp = createTableFrames(renderer, spriteSheetExp, 7, 7);

    Uint32 t = SDL_GetTicks(), nt;
     set<char> keysPressed; // Define keysPressed set here
    // tant que ce n'est pas la fin ...
    while (!quit) {
        Uint32 elapsed_time = SDL_GetTicks() - timer;
        timer = SDL_GetTicks();
        nt = SDL_GetTicks();
        if (nt-t>100/3) {
            jeu.update();
            t = nt;
        }
        if (jeu.v.getPVObj()<=0){
            quit=true;
        }
        // Process all pending events
        while (SDL_PollEvent(&events)) {
            switch (events.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    switch (events.key.keysym.scancode) {
                        case SDL_SCANCODE_W:
                            keysPressed.insert('z');
                            break;
                        case SDL_SCANCODE_S:
                            keysPressed.insert('s');
                            break;
                        case SDL_SCANCODE_A:
                            keysPressed.insert('q');
                            break;
                        case SDL_SCANCODE_D:
                            keysPressed.insert('d');
                            break;
                        case SDL_SCANCODE_V:
                            keysPressed.insert('v');
                            break;
                        case SDL_SCANCODE_ESCAPE:
                        case SDL_SCANCODE_P:
                            quit = true;
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_KEYUP:
                    switch (events.key.keysym.scancode) {
                        case SDL_SCANCODE_W:
                            keysPressed.erase('z');
                            break;
                        case SDL_SCANCODE_S:
                            keysPressed.erase('s');
                            break;
                        case SDL_SCANCODE_A:
                            keysPressed.erase('q');
                            break;
                        case SDL_SCANCODE_D:
                            keysPressed.erase('d');
                            break;
                        case SDL_SCANCODE_V:
                            keysPressed.erase('v');
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }

        // Update the game state with the current key presses
        jeu.actionClavier(keysPressed);
    
        // Pass the set of pressed keys to the actionClavier method
        jeu.actionClavier(keysPressed);

		// on affiche le jeu sur le buffer caché
		sdlAff();

        //affichage des explosions
        for (unsigned int i = 0; i<jeu.explosions.size(); i++){
            if (jeu.explosions[i].currentFrame > 49){
                jeu.explosions.erase(jeu.explosions.begin()+i);
            }
            else {
                displayAnimFrame(renderer, table_exp, spriteSheetExp,
                jeu.explosions[i].currentFrame, int(jeu.explosions[i].posX),
                int(jeu.explosions[i].posY), int(jeu.explosions[i].scalingFactor));
                jeu.explosions[i].currentFrame += 1;
            }
        }

		// on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans la boucle)
        SDL_RenderPresent(renderer);
        // delay if necessary to maintain frame rate
        if (elapsed_time < FRAME_TIME) {
            SDL_Delay(FRAME_TIME - elapsed_time);}
	}
    cout << "Score : " << jeu.score << endl;
    jeu.saveScore();
}



// --------------------- SDL MULTIJOUEUR --------------------

SDLMulti::SDLMulti () : jeu() {
    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Erreur lors de l'initialisation de la SDL : " << 
            SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    if (TTF_Init() != 0) {
        cout << "Erreur lors de l'initialisation de la SDL_ttf : " << 
            TTF_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if( !(IMG_Init(imgFlags) & imgFlags)) {
        cout << "SDL_image could not initialize! SDL_image Error: " << 
            IMG_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    // if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    // {
    //     cout << "SDL_mixer could not initialize! SDL_mixer Error: " << 
    //         Mix_GetError() << endl;
    //     cout << "No sound !!!" << endl;
    //     //SDL_Quit();exit(1);
    //     withSound = false;
    // }
    // else withSound = true;

	int dimx, dimy;
	dimx = jeu.t.getDimX();
	dimy = jeu.t.getDimY();

    // Creation de la fenetre
    window = SDL_CreateWindow("Staresiod", SDL_WINDOWPOS_CENTERED, 
    SDL_WINDOWPOS_CENTERED, dimx, dimy, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == nullptr) {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() 
        << endl; 
        SDL_Quit(); 
        exit(1);
    }

    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    // IMAGES
    im_background.loadFromFile("data/background.png",renderer);
    im_vaissBlue.loadFromFile("data/shipBlue.png",renderer);
    im_vaissPink.loadFromFile("data/shipPink.png",renderer);
    im_vaissBlueMove.loadFromFile("data/shipBlueMoving.png",renderer);
    im_vaissPinkMove.loadFromFile("data/shipPinkMoving.png",renderer);
    im_projectile.loadFromFile("data/laser.png",renderer);
    im_asteroide1.loadFromFile("data/asteroide1.png",renderer);
    im_asteroide2.loadFromFile("data/asteroide2.png",renderer);
    im_asteroide3.loadFromFile("data/asteroide3.png",renderer);
    im_asteroide4.loadFromFile("data/asteroide4.png",renderer);
    im_asteroide5.loadFromFile("data/asteroide5.png",renderer);
    im_powerup_t1.loadFromFile("data/powerUp_explosion.png",renderer);
    im_powerup_t2.loadFromFile("data/powerUp_invulnerability.png",renderer);
    im_powerup_t3.loadFromFile("data/powerUp_speed.png",renderer);
    im_powerup_t4.loadFromFile("data/powerUp_drill.png",renderer);

    // FONTS
    font = TTF_OpenFont("data/DejaVuSansCondensed.ttf",50);
    if (font == nullptr)
        font = TTF_OpenFont("../data/DejaVuSansCondensed.ttf",50);
    if (font == nullptr) {
            cout << "Failed to load DejaVuSansCondensed.ttf! SDL_TTF Error: "
            << TTF_GetError() << endl; 
            SDL_Quit(); 
            exit(1);
	}
	font_color.r = 50;font_color.g = 50;font_color.b = 255;


    // SONS
    // if (withSound)
    // {
    //     sound = Mix_LoadWAV("data/son.wav");
    //     if (sound == nullptr) 
    //         sound = Mix_LoadWAV("../data/son.wav");
    //     if (sound == nullptr) {
    //             cout << "Failed to load son.wav! SDL_mixer Error: " 
    //             << Mix_GetError() << endl; 
    //             SDL_Quit();
    //             exit(1);
    //     }
    // }
}

SDLMulti::~SDLMulti () {
    // if (withSound) Mix_Quit();
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

SDL_Rect* SDLMulti::createTableFrames(SDL_Renderer* renderer, SDL_Texture* spriteSheet,
    int nbCols, int nbLines, int displayScale) {
    int textureWidth, textureHeight;
    SDL_QueryTexture(spriteSheet, NULL, NULL, &textureWidth, &textureHeight);
    const int FRAME_WIDTH = textureWidth / nbCols; // Assuming equal-sized frames
    const int FRAME_HEIGHT = textureHeight / nbLines;

    // Calculate the coordinates of each frame on the sprite sheet
    int NUM_FRAMES = nbCols * nbLines;
    SDL_Rect* frames = new SDL_Rect[NUM_FRAMES];
    for (int i = 0; i < NUM_FRAMES; ++i) {
        int row = i / nbCols;
        int col = i % nbCols;
        frames[i] = { col * FRAME_WIDTH, row * FRAME_HEIGHT, FRAME_WIDTH, FRAME_HEIGHT };
    }
    return frames;
}

void SDLMulti::displayAnimFrame(SDL_Renderer* renderer, SDL_Rect* tab,
    SDL_Texture* spriteSheet, int counter, int posX, int posY, float displayScale) {
    const int FRAME_WIDTH = tab[0].w;  // Assuming equal-sized frames
    const int FRAME_HEIGHT = tab[0].h;
    const int DISPLAY_WIDTH = FRAME_WIDTH * displayScale;
    const int DISPLAY_HEIGHT = FRAME_HEIGHT * displayScale;
    SDL_Rect animationRect = { posX-DISPLAY_WIDTH/2, posY-DISPLAY_HEIGHT/2,
     DISPLAY_WIDTH, DISPLAY_HEIGHT };

    // Set the texture and source rectangle for the current frame
    SDL_RenderCopy(renderer, spriteSheet, &tab[counter], &animationRect);
}




void SDLMulti::sdlAffMulti () {
	//Remplir l'écran de blanc
    SDL_SetRenderDrawColor(renderer, 230, 240, 255, 255);
    SDL_RenderClear(renderer);

    const PowerUp& powerup = jeu.p;
	const Vaisseau& vaiss = jeu.v;
    const Vaisseau& vaiss2 = jeu.w;
    //Afficher le background oh yeah B)
    im_background.draw(renderer, 0, 0, jeu.t.getDimX(), 
        jeu.t.getDimY());

	// Afficher le sprite des vaisseaux
    if(!(vaiss.getDetruitObj())) {
        if (vaiss.indice_acc ==0) {
	    im_vaissBlue.draw(renderer,
            vaiss.getPosObj().getX() - vaiss.getTailleObj()/2,
            vaiss.getPosObj().getY() - vaiss.getTailleObj()/2,
            50.0,
            50.0,
            (vaiss.getPosAngObj()+M_PI/2) * 180.0 / M_PI);
        }
        else {
	    im_vaissBlueMove.draw(renderer,
            vaiss.getPosObj().getX() - vaiss.getTailleObj()/2,
            vaiss.getPosObj().getY() - vaiss.getTailleObj()/2,
            50.0,
            50.0,
            (vaiss.getPosAngObj()+M_PI/2) * 180.0 / M_PI);
        }
    }
    
    if(!(vaiss2.getDetruitObj())) {
        if (vaiss2.indice_acc ==0) {
	    im_vaissPink.draw(renderer,
            vaiss2.getPosObj().getX() - vaiss2.getTailleObj()/2,
            vaiss2.getPosObj().getY() - vaiss2.getTailleObj()/2,
            50.0,
            50.0,
            (vaiss2.getPosAngObj()+M_PI/2) * 180.0 / M_PI);
        }
        else {
	    im_vaissPinkMove.draw(renderer,
            vaiss2.getPosObj().getX() - vaiss2.getTailleObj()/2,
            vaiss2.getPosObj().getY() - vaiss2.getTailleObj()/2,
            50.0,
            50.0,
            (vaiss2.getPosAngObj()+M_PI/2) * 180.0 / M_PI);
        }
    }
    

	// Afficher les sprites des projectiles
    if(!(vaiss.getDetruitObj())) {
        for (int i = 0; i<(int)vaiss.projectiles.size(); i++)
	        im_projectile.draw(renderer,
                vaiss.projectiles[i].getPos().getX() - 5/2,
                vaiss.projectiles[i].getPos().getY() - 5/2,
                8,
                3,
                vaiss.projectiles[i].getPosAng() * 180.0 / M_PI);
    }

    if(!(vaiss2.getDetruitObj())) {
        for (int i = 0; i<(int)vaiss2.projectiles.size(); i++)
	        im_projectile.draw(renderer,
                vaiss2.projectiles[i].getPos().getX() - 5/2,
                vaiss2.projectiles[i].getPos().getY() - 5/2,
                8,
                3,
                vaiss2.projectiles[i].getPosAng() * 180.0 / M_PI);
    }

    //Afficher les sprites des asteroides
    for (int i = 0; i<(int)jeu.asteroides.size(); i++){
        switch(int(jeu.asteroides[i].getTaille())){
            case 20:
                im_asteroide1.draw(renderer,
                jeu.asteroides[i].getPos().getX()- jeu.asteroides[i].getTaille()/2, 
                jeu.asteroides[i].getPos().getY()- jeu.asteroides[i].getTaille()/2,
                jeu.asteroides[i].getTaille(),
                jeu.asteroides[i].getTaille(),
                jeu.asteroides[i].getPosAng()* 180.0 / M_PI);
                break;
            case 40:
                im_asteroide2.draw(renderer,
                jeu.asteroides[i].getPos().getX()- jeu.asteroides[i].getTaille()/2, 
                jeu.asteroides[i].getPos().getY()- jeu.asteroides[i].getTaille()/2,
                jeu.asteroides[i].getTaille(),
                jeu.asteroides[i].getTaille(),
                jeu.asteroides[i].getPosAng()* 180.0 / M_PI);
                break;
            case 60:
                im_asteroide3.draw(renderer,
                jeu.asteroides[i].getPos().getX()- jeu.asteroides[i].getTaille()/2, 
                jeu.asteroides[i].getPos().getY()- jeu.asteroides[i].getTaille()/2,
                jeu.asteroides[i].getTaille(),
                jeu.asteroides[i].getTaille(),
                jeu.asteroides[i].getPosAng()* 180.0 / M_PI);
                break;
            case 80:
                im_asteroide4.draw(renderer,
                jeu.asteroides[i].getPos().getX()- jeu.asteroides[i].getTaille()/2, 
                jeu.asteroides[i].getPos().getY()- jeu.asteroides[i].getTaille()/2,
                jeu.asteroides[i].getTaille(),
                jeu.asteroides[i].getTaille(),
                jeu.asteroides[i].getPosAng()* 180.0 / M_PI);
                break;
            case 100:
                im_asteroide5.draw(renderer,
                jeu.asteroides[i].getPos().getX()- jeu.asteroides[i].getTaille()/2, 
                jeu.asteroides[i].getPos().getY()- jeu.asteroides[i].getTaille()/2,
                jeu.asteroides[i].getTaille(),
                jeu.asteroides[i].getTaille(),
                jeu.asteroides[i].getPosAng()* 180.0 / M_PI);
                break;
            default:
                break;
        }
    }
    
    //Afficher le sprite du powerup
    if(powerup.getActivation()) {
        switch(powerup.getType()) {
            case 1: im_powerup_t1.draw(renderer,powerup.getPos().getX()-25,
                powerup.getPos().getY()-20,40,40);
                break;
            case 2: im_powerup_t2.draw(renderer,powerup.getPos().getX()-25,
                powerup.getPos().getY()-20,40,40);
                break;
            case 3: im_powerup_t3.draw(renderer,powerup.getPos().getX()-25,
                powerup.getPos().getY()-20,40,40);
                break;
            case 4: im_powerup_t4.draw(renderer,powerup.getPos().getX()-25,
                powerup.getPos().getY()-20,40,40);
                break;
            default: break;
    }
    }
    
    //Afficher le score
    SDL_Color couleur = {180, 180, 180};

    // Affichage du scoreV en haut à gauche
    SDL_Surface* surfaceScoreV = TTF_RenderText_Solid(font, ("SCORE J1 : " + to_string(jeu.scoreV)).c_str(), couleur);
    SDL_Texture* textureScoreV = SDL_CreateTextureFromSurface(renderer, surfaceScoreV);
    SDL_Rect scoreRectV = {25, 25, surfaceScoreV->w/2, surfaceScoreV->h/2};
    SDL_RenderCopy(renderer, textureScoreV, NULL, &scoreRectV);
    SDL_FreeSurface(surfaceScoreV);
    SDL_DestroyTexture(textureScoreV);

    // Affichage du scoreW en haut à droite
    SDL_Surface* surfaceScoreW = TTF_RenderText_Solid(font, ("SCORE J2 : " + to_string(jeu.scoreW)).c_str(), couleur);
    SDL_Texture* textureScoreW = SDL_CreateTextureFromSurface(renderer, surfaceScoreW);
    SDL_Rect scoreRectW = {jeu.t.getDimX() - 25 - surfaceScoreW->w/2, 25, surfaceScoreW->w/2, surfaceScoreW->h/2};
    SDL_RenderCopy(renderer, textureScoreW, NULL, &scoreRectW);
    SDL_FreeSurface(surfaceScoreW);
    SDL_DestroyTexture(textureScoreW);


}

void SDLMulti::sdlBoucleMulti () {
    SDL_Event events;
    bool quit = false;

    SDL_Texture* spriteSheetExp = IMG_LoadTexture(renderer, "data/explosion_sheet.png");
    SDL_Rect* table_exp = createTableFrames(renderer, spriteSheetExp, 7, 7);

    Uint32 t = SDL_GetTicks(), nt;
     set<char> keysPressed; // Define keysPressed set here
    while (!quit) {
        Uint32 elapsed_time = SDL_GetTicks() - timer;
        timer = SDL_GetTicks();
        nt = SDL_GetTicks();
        if (nt-t>100/3) {
            jeu.update();
            t = nt;
        }
        if (jeu.v.getPVObj()<=0 && jeu.w.getPVObj()<=0){
            SDL_Delay(500);
            quit=true;
        }
        // Process all pending events
        while (SDL_PollEvent(&events)) {
            switch (events.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    switch (events.key.keysym.scancode) {
                        case SDL_SCANCODE_W:
                            keysPressed.insert('z');
                            break;
                        case SDL_SCANCODE_S:
                            keysPressed.insert('s');
                            break;
                        case SDL_SCANCODE_A:
                            keysPressed.insert('q');
                            break;
                        case SDL_SCANCODE_D:
                            keysPressed.insert('d');
                            break;
                        case SDL_SCANCODE_V:
                            keysPressed.insert('v');
                            break;
                        case SDL_SCANCODE_O:
                            keysPressed.insert('o');
                            break;
                        case SDL_SCANCODE_K:
                            keysPressed.insert('k');
                            break;
                        case SDL_SCANCODE_L:
                            keysPressed.insert('l');
                            break;
                        case SDL_SCANCODE_SEMICOLON:
                            keysPressed.insert('m');
                            break;
                        case SDL_SCANCODE_P:
                            keysPressed.insert('p');
                            break;
                        case SDL_SCANCODE_ESCAPE:
                            quit = true;
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_KEYUP:
                    switch (events.key.keysym.scancode) {
                        case SDL_SCANCODE_W:
                            keysPressed.erase('z');
                            break;
                        case SDL_SCANCODE_S:
                            keysPressed.erase('s');
                            break;
                        case SDL_SCANCODE_A:
                            keysPressed.erase('q');
                            break;
                        case SDL_SCANCODE_D:
                            keysPressed.erase('d');
                            break;
                        case SDL_SCANCODE_V:
                            keysPressed.erase('v');
                            break;
                        case SDL_SCANCODE_O:
                            keysPressed.erase('o');
                            break;
                        case SDL_SCANCODE_K:
                            keysPressed.erase('k');
                            break;
                        case SDL_SCANCODE_L:
                            keysPressed.erase('l');
                            break;
                        case SDL_SCANCODE_SEMICOLON:
                            keysPressed.erase('m');
                            break;
                        case SDL_SCANCODE_P:
                            keysPressed.erase('p');
                            break;
                        default:
                            break;
                        
                    }
                    break;
                default:
                    break;
            }
        }

        // Update the game state with the current key presses
        jeu.actionClavier(keysPressed);
    
        // Pass the set of pressed keys to the actionClavier method
        jeu.actionClavier(keysPressed);

		// on affiche le jeu sur le buffer caché
		sdlAffMulti();

        //affichage des explosions
        for (unsigned int i = 0; i<jeu.explosions.size(); i++){
            if (jeu.explosions[i].currentFrame > 49){
                jeu.explosions.erase(jeu.explosions.begin()+i);
            }
            else {
                displayAnimFrame(renderer, table_exp, spriteSheetExp,
                jeu.explosions[i].currentFrame, int(jeu.explosions[i].posX),
                int(jeu.explosions[i].posY), int(jeu.explosions[i].scalingFactor));
                jeu.explosions[i].currentFrame += 1;
            }
        }

		// on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans la boucle)
        SDL_RenderPresent(renderer);
        // delay if necessary to maintain frame rate
        if (elapsed_time < FRAME_TIME) {
            SDL_Delay(FRAME_TIME - elapsed_time);}
	}
    cout << "Score de J1 : " << jeu.scoreV << endl;
    cout << "Score de J2 : " << jeu.scoreW << endl;
    if (jeu.scoreV>jeu.scoreW) {
        cout << "J1 a gagné =)" << endl;
    } else if (jeu.scoreV<jeu.scoreW) {
        cout << "J2 a gagné =)" << endl;
    } else {
        cout << "Egalité =)" << endl;
    }
    jeu.saveScore();
}