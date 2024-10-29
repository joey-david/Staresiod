/**

@file JeuMulti.h
@brief Déclaration de la classe JeuMulti
*/
#ifndef _JEUMULTI
#define _JEUMULTI

#include "Vaisseau.h"
#include "Terrain.h"
#include "PowerUp.h"
#include <stdlib.h>
#include <random>
#include <set>
using namespace std;

/**

@brief Classe représentant un jeu multijoueur
*/
class JeuMulti {
    public:
        Vaisseau v; /**< Le vaisseau du joueur 1 */
        Vaisseau w; /**< Le vaisseau du joueur 2 */
        int PU; /**< Le power-up en jeu */
        int scoreV; /**< Le score du joueur 1 */
        int scoreW; /**< Le score du joueur 2 */
        Terrain t; /**< Le terrain */
        int nb_aster; /**< Le nombre d'astéroïdes */
        PowerUp p; /**< Le power-up */
        vector<Objet> asteroides; /**< Les astéroïdes */
        JeuMulti(); /**< Constructeur par défaut */
        float vmax; /**< Vitesse maximale */
        int elapsed_frames; /**< Nombre de frames écoulées depuis le début du jeu */
         /**
        * @brief Structure représentant une explosion
        */
        struct Explosion {
            int posX; /**< La position X de l'explosion */
            int posY; /**< La position Y de l'explosion */
            int currentFrame = 0; /**< Le nombre de frames écoulées depuis le début de l'explosion */
            float scalingFactor = 1.0; /**< Le facteur d'échelle de l'explosion */
        };
        vector<Explosion> explosions; /**< Les explosions */

        /*dans getUpdate, on effectue tous les tests de collision, de sortie de terrain, 
        On compte le nombre d'aster*/
        /**

        @brief genere les astéroïdes nécessaires
        */
        void genereAster();

        /**

        @brief Met à jour les positions de tous les objets dans le jeu
        */
        void update();

        /**

        @brief Effectue tous les tests de collision, de sortie de terrain et compte le nombre d'astéroïdes
        */
        void getUpdate();

        /**

        @brief Gère les collisions entre les différents objets dans le jeu
        */
        void collisionnage();

        /**

        @brief Met à jour les positions des vaisseaux et des projectiles dans le jeu
        */
        void getUpdateVaiss();

        /**

        @brief Met à jour les positions des astéroïdes dans le jeu
        */
        void getUpdateAster();

        /**

        @brief Met à jour les positions de tous les objets dans le jeu et crée de nouveaux objets si nécessaire
        */
        void setUpdate();

        /**

        @brief Génère éventuellement de nouveaux astéroïdes dans le jeu
        */
        void setUpdateAster();

        /**

        @brief Génère éventuellement de nouveaux power-ups dans le jeu
        */
        void setUpdatePowerUp();

        /**

        @brief Gère les inputs clavier du joueur pour les vaisseaux et les projectiles
        @param touches Ensemble de touches clavier appuyées
        */
        void actionClavier(set<char>& touches);
        /**

        @brief Met à jour les positions des vaisseaux et des projectiles dans le jeu
        */
        void setUpdateVaiss();

        /**

        @brief Enregistre le score actuel dans un fichier
        */
        void saveScore() const;

        /**

        @brief Quitte le jeu
        */
        void exit();

        /**

        @brief Lance une série de tests de régression pour vérifier le bon fonctionnement du jeu
        */
        void testRegression();
};


#endif