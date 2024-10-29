/**

@file Menu.h
@brief Définition de la classe Menu
*/
#ifndef _MENU
#define _MENU

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_render.h>
#include "Terrain.h"

/**

@class Menu

@brief Gère l'affichage et la sélection d'options dans un menu.
*/
class Menu {
	public:
		/**

		@brief Constructeur de la classe Menu.
		@param options Tableau de chaînes de caractères représentant les différentes options du menu.
		@param nbOptions Nombre d'options dans le menu.
		*/
		Menu(const std::string options[], int nbOptions);
		/**

		@brief Destructeur de la classe Menu.
		*/
		~Menu();
		/**

		@brief Affiche le menu en surbrillance à l'option donnée.
		@param choix Index de l'option à mettre en surbrillance.
		*/
		void afficher(int choix);
		/**

		@brief Indique si une sélection est en cours.
		@return True si une sélection est en cours, false sinon.
		*/
		bool selectionEnCours() const;
		/**

		@brief Récupère l'index de l'option sélectionnée.
		@return L'index de l'option sélectionnée.
		*/
		int obtenirChoix() const;
		/**

		@brief Gère les événements clavier du menu.
		@param evenement Événement clavier à gérer.
		*/
		void gererEvenements(const SDL_Event& evenement);
		bool multijoueur; /**< Indique si le mode multijoueur est activé. */
		Terrain t; /**< Terrain du jeu. */
		/**

		@brief Lance la boucle du menu.
		*/
		void menuBoucle();
	private:
		/** Renderer SDL pour le menu. */
		SDL_Renderer* m_renderer;
		/** Police de caractères du menu. */
		TTF_Font* m_police;
		/** Couleur de la police de caractères du menu. */
		SDL_Color m_couleurTexte;
		/** Rectangle pour positionner les options du menu. */
		SDL_Rect m_rect; 
		/** Tableau de textures SDL pour les options du menu. */
		SDL_Texture** m_textures; 
		/** Nombre d'options dans le menu. */
		int m_nbOptions; 
		/** Index de l'option sélectionnée. */
		int m_choix; 
		/** Indique si une sélection est en cours. */
		bool m_selectionEnCours; 
};

#endif