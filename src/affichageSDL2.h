/**

@file JeuSDL.h
@brief Définition de la classe JeuSDL et de la classe Image pour gérer les images avec SDL2.
*/
#ifndef _JEUSDL
#define _JEUSDL
#include "Jeu.h"
#include "JeuMulti.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

/**

@brief Pour gérer une image avec SDL2
*/
class Image {
    private:

        SDL_Surface * m_surface; //!< \brief Surface SDL2 de l'image
        SDL_Texture * m_texture; //!< \brief Texture SDL2 de l'image
        bool m_hasChanged; //!< \brief Indique si l'image a été modifiée depuis sa dernière utilisation


    public:
        /**
        * @brief Constructeur de la classe Image
        */
        Image () ;
        /**
         * @brief Destructeur de la classe Image
         */
        ~Image();

        /**
         * @brief Charge une image depuis un fichier et la convertit en texture SDL2
         * @param filename Le nom du fichier contenant l'image
         * @param renderer Le renderer SDL2 pour créer la texture
         */
        void loadFromFile (const char* filename, SDL_Renderer * renderer);

        /**
         * @brief Convertit la surface actuelle en texture SDL2
         * @param renderer Le renderer SDL2 pour créer la texture
         */
        void loadFromCurrentSurface (SDL_Renderer * renderer);

        /**
         * @brief Dessine l'image sur le renderer SDL2
         * @param renderer Le renderer SDL2 sur lequel dessiner l'image
         * @param x La position horizontale de l'image
         * @param y La position verticale de l'image
         * @param w La largeur de l'image (optionnel)
         * @param h La hauteur de l'image (optionnel)
         * @param angle L'angle de rotation de l'image (optionnel)
         */
        void draw (SDL_Renderer * renderer, int x, int y, int w=-1, int h=-1, double angle =0);

        /**
         * @brief Accesseur pour la texture SDL2 de l'image
         * @return La texture SDL2 de l'image
         */
        SDL_Texture * getTexture() const;

        /**
         * @brief Mutateur pour la surface SDL2 de l'image
         * @param surf La nouvelle surface SDL2 de l'image
         */
        void setSurface(SDL_Surface * surf);
};



/**
    La classe gerant le jeu avec un affichage SDL
*/
class SDLSimple {

    private :

        Jeu jeu;

        SDL_Window* window;             //!< \brief Fenêtre SDL
        SDL_Renderer* renderer;         //!< \brief Renderer SDL

        TTF_Font* font;                 //!< \brief Police d'écriture
        Image font_im;                  //!< \brief Image pour la police d'écriture
        SDL_Color font_color;           //!< \brief Couleur de la police d'écriture

        Mix_Chunk* sound;               //!< \brief Effet sonore
        bool withSound;                 //!< \brief Booléen pour savoir si le son est activé

        Image im_background;            //!< \brief Image de fond
        Image im_vaisseau;              //!< \brief Image du vaisseau
        Image im_vaissAcc1;             //!< \brief Image du vaisseau accéléré 1
        Image im_vaissAcc2;             //!< \brief Image du vaisseau accéléré 2
        Image im_vaissBra1;             //!< \brief Image du vaisseau freinant 1
        Image im_vaissBra2;             //!< \brief Image du vaisseau freinant 2
        Image im_projectile;            //!< \brief Image du projectile
        Image im_asteroide1;            //!< \brief Image de l'astéroïde de type 1
        Image im_asteroide2;            //!< \brief Image de l'astéroïde de type 2
        Image im_asteroide3;            //!< \brief Image de l'astéroïde de type 3
        Image im_asteroide4;            //!< \brief Image de l'astéroïde de type 4
        Image im_asteroide5;            //!< \brief Image de l'astéroïde de type 5
        Image im_powerup_t1;            //!< \brief Image du power-up de type 1
        Image im_powerup_t2;            //!< \brief Image du power-up de type 2
        Image im_powerup_t3;            //!< \brief Image du power-up de type 3
        Image im_powerup_t4;            //!< \brief Image du power-up de type 4
        Image explosions;               //!< \brief Image des explosions

        bool souris;                    //!< \brief Booléen pour savoir si la souris est utilisée
        bool touche;                    //!< \brief Booléen pour savoir si le clavier est utilisé


    public :
        /** @brief Constructeur par défaut de la classe SDLSimple.
        */
        SDLSimple ();
        /**
         * @brief Destructeur de la classe SDLSimple.
         */
        ~SDLSimple ();
        
        /**
         * @brief Boucle principale de la fenêtre SDL simple.
         */
        void sdlBoucle ();
        
        /**
         * @brief Fonction d'affichage de la fenêtre SDL simple.
         */
        void sdlAff ();
        
        /**
         * @brief Création d'un tableau de SDL_Rect représentant les frames d'une texture.
         * @param renderer Le renderer SDL.
         * @param spriteSheet La texture SDL contenant les frames.
         * @param nbCols Le nombre de colonnes de frames.
         * @param nbLines Le nombre de lignes de frames.
         * @param displayScale L'échelle de l'affichage (1 par défaut).
         * @return Un pointeur vers le tableau de frames créé.
         */
        SDL_Rect* createTableFrames (SDL_Renderer* renderer, SDL_Texture* spriteSheet,
            int nbCols, int nbLines, int displayScale = 1);
        
        /**
         * @brief Fonction d'affichage d'une frame d'animation.
         * @param renderer Le renderer SDL.
         * @param tab Le tableau de SDL_Rect représentant les frames.
         * @param spriteSheet La texture SDL contenant les frames.
         * @param counter Le compteur d'animation.
         * @param posX La position en X de l'affichage.
         * @param posY La position en Y de l'affichage.
         * @param displayScale L'échelle de l'affichage.
         */
        void displayAnimFrame (SDL_Renderer* renderer, SDL_Rect* tab, 
            SDL_Texture* spriteSheet, int counter, int posX, int posY,
            float displayScale);

};


class SDLMulti {

    private :

        JeuMulti jeu;

        SDL_Window* window;             //!< \brief Fenêtre SDL
        SDL_Renderer* renderer;         //!< \brief Renderer SDL

        TTF_Font * font; //!< police de caractères utilisée pour l'affichage du score
        Image font_im; //!< image représentant la police de caractères
        SDL_Color font_color; //!< couleur de la police de caractères

        Mix_Chunk * sound; //!< effets sonores du jeu
        bool withSound; //!< pour savoir si les effets sonores sont activés ou non

        Image im_background; //!< image de fond
        Image im_vaissBlue; //!< image du vaisseau bleu
        Image im_vaissBlueMove; //!< image du vaisseau bleu en mouvement
        Image im_vaissPink; //!< image du vaisseau rose
        Image im_vaissPinkMove; //!< image du vaisseau rose en mouvement
        Image im_projectile; //!< image des projectiles
        Image im_asteroide1; //!< image des astéroides de type 1
        Image im_asteroide2; //!< image des astéroides de type 2
        Image im_asteroide3; //!< image des astéroides de type 3
        Image im_asteroide4; //!< image des astéroides de type 4
        Image im_asteroide5; //!< image des astéroides de type 5
        Image im_powerup_t1; //!< image des power-ups de type 1
        Image im_powerup_t2; //!< image des power-ups de type 2
        Image im_powerup_t3; //!< image des power-ups de type 3
        Image im_powerup_t4; //!< image des power-ups de type 4
        Image explosions; //!< image représentant les explosions

        bool souris; //!< pour savoir si la souris est utilisée ou non
        bool touche; //!< pour savoir si le clavier est utilisé ou non


    public :
        /** @brief Constructeur par défaut de la classe SDLMulti.
        */
        SDLMulti ();
         /**
         * @brief Destructeur de la classe SDLMulti.
         */
        ~SDLMulti ();
        
        /**
         * @brief Boucle principale de la fenêtre SDL multi-joueurs.
         */
        void sdlBoucleMulti();
        
        /**
         * @brief Fonction d'affichage de la fenêtre SDL multi-joueurs.
         */
        void sdlAffMulti ();
        
        /**
         * @brief Création d'un tableau de SDL_Rect représentant les frames d'une texture.
         * @param renderer Le renderer SDL.
         * @param spriteSheet La texture SDL contenant les frames.
         * @param nbCols Le nombre de colonnes de frames.
         * @param nbLines Le nombre de lignes de frames.
         * @param displayScale L'échelle de l'affichage (1 par défaut).
         * @return Un pointeur vers le tableau de frames créé.
         */
        SDL_Rect* createTableFrames (SDL_Renderer* renderer, SDL_Texture* spriteSheet,
            int nbCols, int nbLines, int displayScale = 1);
        
        /**
         * @brief Fonction d'affichage d'une frame d'animation.
         * @param renderer Le renderer SDL.
         * @param tab Le tableau de SDL_Rect représentant les frames.
         * @param spriteSheet La texture SDL contenant les frames.
         * @param counter Le compteur d'animation.
         * @param posX La position en X de l'affichage.
         * @param posY La position en Y de l'affichage.
         * @param displayScale L'échelle de l'affichage.
         */

        void displayAnimFrame (SDL_Renderer* renderer, SDL_Rect* tab, 
            SDL_Texture* spriteSheet, int counter, int posX, int posY,
            float displayScale);
};

#endif

