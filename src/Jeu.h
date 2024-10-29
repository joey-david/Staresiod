/**

@file Jeu.h
@brief Définition de la classe Jeu
*/
#ifndef _JEU
#define _JEU

#include "Vaisseau.h"
#include "Terrain.h"
#include "PowerUp.h"
#include <stdlib.h>
#include <random>
#include <set>

/**

@class Jeu

@brief Classe représentant le jeu

La classe gère les éléments du jeu, tels que le vaisseau, le terrain, les power-ups et les astéroïdes.
*/
class Jeu {
    public:
        /** Instance du vaisseau */
        Vaisseau v;

        /** Score du joueur */
        int score;

        /** Terrain de jeu */
        Terrain t;

        /** Nombre d'astéroïdes */
        int nb_aster;

        /** Power-up */
        PowerUp p;

        /** Vector contenant tous les astéroïdes */
        vector<Objet> asteroides;

        /** Constructeur de Jeu */
        Jeu();

        /** Vitesse maximale */
        float vmax;

        /** Nombre de frames écoulées */
        int elapsed_frames;

        /** Structure pour les explosions */
        struct Explosion {
            int posX;
            int posY;
            int currentFrame = 0;
            float scalingFactor = 1.0;
        };
        /** Vector contenant toutes les explosions */
        vector<Explosion> explosions;
        
        /*dans getUpdate, on effectue tous les tests de collision, de sortie de terrain, 
        On compte le nombre d'aster*/
        /**

        @brief Génère un nombre fixe d'astéroïdes et les ajoute au vecteur asteroides.
        */
        void genereAster();  
        /**

        @brief Appelle tous les mutateurs et accesseurs update dans l'ordre.
        */      
        void update();
        /**

        @brief Fonction qui appelle les différents accesseurs update.
        */
        void getUpdate();
        /**

        @brief Vérifie si les objets sont en collision les uns avec les autres.
        */
        void collisionnage();
        /**
        
        @brief Check les points de vie et la pos du vaisseau et des projectiles.
        */
        void getUpdateVaiss(); //et des projectiles
        /**
        
        @brief Check les points de vie et la pos des asteroïdes.
        */
        void getUpdateAster();
        /**
        
        @brief Appelle les différents mutateurs updates.
        */
        void setUpdate();
        /**

        @brief Met à jour les astéroïdes du jeu en déplaçant les objets selon leurs trajectoires et les inputs.
        */
        void setUpdateAster(); //génération éventuelle d'astéroïdes
        /**

        @brief Met à jour les états des powerups.
        */
        void setUpdatePowerUp();
        /**

        @brief Effectue les actions du clavier.
        @param touches L'ensemble des touches pressées.
        */
        void actionClavier(set<char>& touches);
        /**

        @brief Met à jour le vaisseau et les projectiles du jeu en déplaçant les objets selon leurs trajectoires et les inputs.
        */
        void setUpdateVaiss(); //et des projectiles
        /**

        @brief Sauvegarde le score du joueur.
        */
        void saveScore() const;
        /**

        @brief Quitte le jeu.
        */
        void exit();
        /**

        @brief Fonction de test pour la régression.
        */
        void testRegression();
};


#endif