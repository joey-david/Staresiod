/**

@file PowerUp.h
@brief Définition de la classe PowerUp et de ses méthodes.
*/
#ifndef _POWERUP
#define _POWERUP

#include "Vec2.h"

/**

@class PowerUp

@brief Classe représentant un power-up dans le jeu.

La classe PowerUp permet de définir et de manipuler un power-up dans le jeu. Un power-up

est un objet qui peut être collecté par le joueur et qui procure un effet bénéfique pour une

durée limitée.
*/
class PowerUp {
    private:
        int type; /**< Le type de power-up. Les types possibles sont :
        - 1 : destruction des astéroides
        - 2 : invulnérabilité de la vaisseau
        - 3 : augmentation de la vitesse du vaisseau
        - 4 : invulnérabilité des projectiles */
        int cd; /**< Le temps de recharge du power-up en secondes. */
        Vec2 pos; /**< La position du power-up dans l'espace de jeu. */
        float taille; /**< La taille du power-up. */
        bool actif; /**< Un booléen indiquant si le power-up est actif ou non. */
        int cdActif; /**< Le temps de durée d'activation du power-up en secondes. */
        bool activation; /**< Un booléen indiquant si le power-up est en cours d'activation. */

    public:
            /**
            * @brief Constructeur de la classe PowerUp.
            * @param Type Le type de power-up.
            * @param CD Le temps de recharge du power-up.
            * @param Pos La position du power-up dans l'espace de jeu.
            * @param Taille La taille du power-up.
            * @param Actif Indique si le power-up est actif ou non.
            * @param CDActif Le temps de durée d'activation du power-up.
            */
            PowerUp(int Type=0, int CD = 0, Vec2 Pos=Vec2(0,0), float Taille=50,
            bool Actif=false, int CDActif=240);
            int getType() const; /**< Retourne le type de power-up. */
            int getCD() const; /**< Retourne le temps de recharge du power-up. */
            Vec2 getPos() const; /**< Retourne la position du power-up. */
            float getTaille() const; /**< Retourne la taille du power-up. */
            bool getActif() const; /**< Retourne si le power-up est actif ou non. */
            int getCDActif() const; /**< Retourne le temps de durée d'activation du power-up. */
            bool getActivation() const; /**< Retourne si le power-up est en cours d'activation ou non. */

            /**
             * @brief Modifie le type de power-up.
             * @param Type Le nouveau type de power-up.
             */
            void setType(const int& Type);

            /**
             * @brief Modifie le temps de recharge du power-up.
             * @param CD Le nouveau temps de recharge.
             */
            void setCD(const int& CD);

            /**
             * @brief Définit la position du PowerUp.
             * @param Pos : la nouvelle position du PowerUp.
             */
            void setPos(const Vec2& Pos);

            /**
             * @brief Définit la taille du PowerUp.
             * @param Taille : la nouvelle taille du PowerUp.
             */
            void setTaille(const float& Taille);

            /**
             * @brief Définit si le PowerUp est actif ou non.
             * @param Actif : l'état d'activité du PowerUp.
             */
            void setActif(const bool& Actif);

            /**
             * @brief Définit le temps de recharge actuel du PowerUp.
             * @param CDActif : le nouveau temps de recharge actuel du PowerUp.
             */
            void setCDActif(const int& CDActif);

            /**
             * @brief Définit l'état d'activation du PowerUp.
             * @param Activation : l'état d'activation du PowerUp.
             */
            void setActivation(const bool& Activation);

            /**
             * @brief Fonction de test du PowerUp.
             */
            void test();


} ;

#endif