/**

@file Jeu.h
@brief Définition de la classe Jeu.
*/
#ifndef _JEU
#define _JEU

#include "Vaisseau.h"
#include "Terrain.h"
#include "PowerUp.h"
#include <stdlib.h>
#include <random>
using namespace std;

/**

@class Jeu
@brief Classe représentant le jeu.
Cette classe est utilisée pour créer, initialiser, mettre à jour et afficher le jeu.
*/
class JeuEnTxt {
    public:
        Vaisseau v; //!< \brief Le vaisseau.
        int score; //!< \brief Le score.
        Terrain t; //!< \brief Le terrain.
        int nb_aster; //!< \brief Le nombre d'astéroïdes.
        vector<Objet> asteroides; //!< \brief Les astéroïdes.
        JeuEnTxt(); //!< \brief Constructeur par défaut.
        void init() const; //!< \brief Initialise le jeu.
        /*
        * @brief Effectue tous les tests de collision, de sortie de terrain et compte le nombre d'astéroïdes.
        */
        void genereAster();
        void update(); //!< \brief Met à jour le jeu.
        void getUpdate(); //!< \brief Obtient la mise à jour du jeu.
        void collisionnage(); //!< \brief Gère les collisions.
        void getUpdateVaiss(); //!< \brief Obtient la mise à jour du vaisseau et des projectiles.
        void getUpdateAster(); //!< \brief Obtient la mise à jour des astéroïdes.
        void setUpdate(); //!< \brief Déplace tous les objets selon leurs trajectoires et les inputs et crée les nouveaux objets (astéroïdes, projectiles).
        void setUpdateAster(); //!< \brief Génère éventuellement des astéroïdes.
        void actionClavier(const char touche); //!< \brief Gère les actions du clavier.
        void setUpdateVaiss(); //!< \brief Déplace le vaisseau et les projectiles.
        void saveScore() const; //!< \brief Sauvegarde le score.
        void exit(); //!< \brief Quitte le jeu.
        void testRegression(); //!< \brief Effectue les tests de régression.
};
#endif