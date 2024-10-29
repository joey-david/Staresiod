#include "Menu.h"

Menu::Menu(const std::string options[], int nbOptions) :
    m_renderer(nullptr),
    m_police(nullptr),
    m_textures(nullptr),
    m_nbOptions(nbOptions),
    m_choix(0),
    m_selectionEnCours(false)
{
    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Erreur lors de l'initialisation de SDL : " << SDL_GetError()
            << std::endl;
        return;
    }

    // Initialisation de TTF
    if (TTF_Init() == -1) {
        std::cerr << "Erreur lors de l'initialisation de TTF : " << TTF_GetError()
            << std::endl;
        return;
    }

    // Création du renderer
    SDL_Window* window = SDL_CreateWindow("Menu", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, t.getDimX(), t.getDimY(), SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Erreur lors de la création de la fenêtre : " << SDL_GetError()
            << std::endl;
        return;
    }
    m_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!m_renderer) {
        std::cerr << "Erreur lors de la création du renderer : " << SDL_GetError()
            << std::endl;
        return;
    }

    // Chargement de la police
    m_police = TTF_OpenFont("data/DejaVuSansCondensed.ttf", 1);
    if (!m_police) {
        std::cerr << "Erreur lors du chargement de la police : " << TTF_GetError()
            << std::endl;
        return;
    }

    // Initialisation de la couleur du texte
    m_couleurTexte = {150, 150, 150, 255};
    SDL_Texture* frameTexture = IMG_LoadTexture(m_renderer, "data/frame.png");
    
   // Création des textures pour chaque option
    m_textures = new SDL_Texture*[nbOptions];
    for (int i = 0; i < nbOptions; ++i) {
        SDL_Surface* surface = TTF_RenderText_Solid(m_police, options[i].c_str(),
            m_couleurTexte);
        if (!surface) {
            std::cerr << "Erreur lors de la création de la surface : "
                << TTF_GetError() << std::endl;
            return;
        }
        m_textures[i] = SDL_CreateTextureFromSurface(m_renderer, surface);
        if (!m_textures[i]) {
            std::cerr << "Erreur lors de la création de la texture : "
                << SDL_GetError() << std::endl;
            return;
        }
        SDL_FreeSurface(surface);
    }

    // Initialisation du rectangle pour le texte et le cadre
    int hauteurMax = t.getDimX()/2;
    int largeurTotal = 0;
    int optionWidth = 200;
    int optionHeight = 70;
    int optionSpacing = 50;
    for (int i = 0; i < nbOptions; ++i) {
        SDL_QueryTexture(m_textures[i], nullptr, nullptr, &optionWidth, &optionHeight);
        if (optionHeight > hauteurMax) {
            hauteurMax = optionHeight;
        }
        largeurTotal += optionWidth;
    }

    

    /*m_rect.w = frameWidth;  // Width of the frame rectangle
    m_rect.h = frameHeight;  // Height of the frame rectangle*/

    for (int i = 0; i < nbOptions; ++i) {
        int largeur, hauteur;
        SDL_QueryTexture(m_textures[i], nullptr, nullptr, &largeur, &hauteur);

        // Render the frame around the option
        int x = i*(optionWidth+optionSpacing) + 100;
        int y = 2*t.getDimY()/3;
        SDL_Rect frameRect = {x, y, optionWidth, optionHeight};
        SDL_RenderCopy(m_renderer, frameTexture, nullptr, &frameRect);

        // Render the option text
        SDL_Rect textRect = {x, y, largeur, hauteur};
        SDL_RenderCopy(m_renderer, m_textures[i], nullptr, &textRect);
    }
}


Menu::~Menu() {
    // Libération de la mémoire pour les textures
    for (int i = 0; i < m_nbOptions; i++) {
        SDL_DestroyTexture(m_textures[i]);
    }
    delete[] m_textures;

    TTF_CloseFont(m_police);
    TTF_Quit();
    SDL_DestroyRenderer(m_renderer);
    SDL_Quit();
}



void Menu::afficher(int choix) {
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);
    m_rect.y = 10;
    SDL_Texture* frameTexture = IMG_LoadTexture(m_renderer, "data/frame.png");
    int nbOptions = 2;
    int hauteurMax = t.getDimX()/2;
    int largeurTotal = 0;
    int optionWidth = 200;
    int optionHeight = 70;
    int optionSpacing = 50;
    for (int i = 0; i < nbOptions; ++i) {
        SDL_QueryTexture(m_textures[i], nullptr, nullptr, &optionWidth, &optionHeight);
        if (optionHeight > hauteurMax) {
            hauteurMax = optionHeight;
        }
        largeurTotal += optionWidth;
    }

    

    /*m_rect.w = frameWidth;  // Width of the frame rectangle
    m_rect.h = frameHeight;  // Height of the frame rectangle*/

    for (int i = 0; i < nbOptions; ++i) {
        int largeur, hauteur;
        SDL_QueryTexture(m_textures[i], nullptr, nullptr, &largeur, &hauteur);

        // Render the frame around the option
        int x = i*(optionWidth+optionSpacing) + 100;
        int y = 3*t.getDimY()/4;
        SDL_Rect frameRect = {x, y, optionWidth, optionHeight};
        SDL_RenderCopy(m_renderer, frameTexture, nullptr, &frameRect);

        // Render the option text
        SDL_Rect textRect = {x, y, largeur, hauteur};
        SDL_RenderCopy(m_renderer, m_textures[i], nullptr, &textRect);
    }
}

bool Menu::selectionEnCours() const {
    return m_selectionEnCours;
}

int Menu::obtenirChoix() const {
    return m_choix;
}

void Menu::gererEvenements(const SDL_Event& evenement) {
    if (evenement.type == SDL_MOUSEBUTTONDOWN) {
        int mouseX = evenement.button.x;
        if (mouseX < t.getDimX()/2){
            m_choix = 0;
            multijoueur = false;
            m_selectionEnCours = true;
        }
        else if (mouseX > t.getDimX()/2){
            m_choix = 1;
        }
            if (m_choix == 1) {
                multijoueur = true;
                m_selectionEnCours = true;
                }
        }
}



void Menu::menuBoucle() {
    bool terminer = false;
    SDL_Texture* menuIm = IMG_LoadTexture(m_renderer, "data/menuImage.png");
    SDL_Texture* menuSP = IMG_LoadTexture(m_renderer, "data/SPSelector.png");
    SDL_Texture* menuMP = IMG_LoadTexture(m_renderer, "data/MPSelector.png");
    SDL_Rect menuImDisplay = {t.getDimX()/8, t.getDimY()/12, 3*t.getDimY()/4, t.getDimX()/2};
    SDL_Rect menuSPDisplay = {t.getDimX()/8, 5*t.getDimY()/8, t.getDimY()/3, t.getDimX()/3};
    SDL_Rect menuMPDisplay = {8*t.getDimX()/15, 5*t.getDimY()/8, t.getDimY()/3, t.getDimX()/3};
    while (!terminer) {
        // Gestion des événements
        SDL_Event evenement;
        while (SDL_PollEvent(&evenement)) {
            if (evenement.type == SDL_QUIT) {
                terminer = true;
            }
            gererEvenements(evenement);
        }
        // Affichage du menu
        afficher(obtenirChoix());
        SDL_RenderCopy(m_renderer, menuIm, nullptr, &menuImDisplay);
        SDL_RenderCopy(m_renderer, menuSP, nullptr, &menuSPDisplay);
        SDL_RenderCopy(m_renderer, menuMP, nullptr, &menuMPDisplay);
        SDL_RenderPresent(m_renderer);
        // Si la sélection est terminée, quitter la boucle
        if (selectionEnCours()) {
            terminer = true;
        }
    }
}
