/**

@file Vaisseau.h
@brief Déclaration de la classe Vaisseau et de ses fonctions membres.
*/
#ifndef _VAISS
#define _VAISS

#include "Objet.h"
#include <vector>

using namespace std;

/**

@class Vaisseau

@brief Classe représentant un vaisseau.

Un vaisseau est un objet qui possède une position, une vitesse, une accélération, une masse, une taille, une orientation, des points de vie, un type,

une cadence de tir et une possibilité de tirer. Il peut aussi contenir des projectiles et un indice d'accélération.
*/

class Vaisseau{
        private:
                Objet o;                        /** L'objet représentant le vaisseau. */
                float cadenceTir;               /** La cadence de tir du vaisseau. */
                int peutTirer;                  /** La possibilité de tirer du vaisseau. */
        public:
                vector<Objet> projectiles;      /** Les projectiles du vaisseau. */
                float indice_acc;               /** L'indice d'accélération du vaisseau. */
                /**
                * @brief Constructeur de la classe Vaisseau.
                * @param Pos La position initiale du vaisseau.
                * @param Vit La vitesse initiale du vaisseau.
                * @param Acc L'accélération initiale du vaisseau.
                * @param Masse La masse du vaisseau.
                * @param Vscal L'échelle de la vitesse du vaisseau.
                * @param Taille La taille du vaisseau.
                * @param PosAng L'angle de position du vaisseau.
                * @param VitAng L'angle de vitesse du vaisseau.
                * @param AccAng L'angle d'accélération du vaisseau.
                * @param PV Les points de vie du vaisseau.
                * @param Type Le type du vaisseau.
                * @param CadenceTir La cadence de tir du vaisseau.
                * @param PeutTirer La possibilité de tirer du vaisseau.
                * @param Indice_acc L'indice d'accélération du vaisseau.
                */
                Vaisseau(Vec2 Pos = Vec2(0,0), Vec2 Vit = Vec2(0,0), Vec2 Acc = Vec2(0,0),
                float Masse = 0, float Vscal = 1.0, float Taille = 50.0, float PosAng = 0,
                float VitAng = 0, float AccAng = 0, int PV = 1, int Type = 0,
                float CadenceTir = 0, int PeutTirer = true, float Indice_acc = 0);
                        
                        //Accesseurs
                /**

                @brief Accesseur pour l'objet représentant le vaisseau.
                @return L'objet représentant le vaisseau.
                */
                Objet getObj() const;
                /**

                @brief Accesseur pour la position de l'objet représentant le vaisseau.
                @return La position de l'objet représentant le vaisseau.
                */
                Vec2 getPosObj() const;
                /**

                @brief Accesseur pour la vitesse de l'objet représentant le vaisseau.
                @return La vitesse de l'objet représentant le vaisseau.
                */
                Vec2 getVitObj() const;
                /**

                @brief Accesseur pour l'accélération de l'objet représentant le vaisseau.
                @return L'accélération de l'objet représentant le vaisseau.
                */
                Vec2 getAccObj() const;
                /**

                @brief Accesseur pour la masse de l'objet représentant le vaisseau.
                @return La masse de l'objet représentant le vaisseau.
                */
                float getMasseObj() const;
                /**

                @brief Accesseur pour l'échelle de la vitesse de l'objet représentant le vaisseau.
                @return L'échelle de la vitesse de l'objet représentant le vaisseau.
                */
                float getVscalObj() const;
                /**

                @brief Accesseur pour l'angle de position de l'objet représentant le vaisseau.
                @return L'angle de position de l'objet représentant le vaisseau.
                */
                float getPosAngObj() const;
                /**

                @brief Accesseur pour la taille de l'objet représentant le vaisseau.
                @return La taille de l'objet représentant le vaisseau.
                */
                float getTailleObj() const;
                /**

                @brief Accesseur pour l'angle de vitesse de l'objet représentant le vaisseau.
                @return L'angle de vitesse de l'objet représentant le vaisseau.
                */
                float getVitAngObj() const;
                /**

                @brief Accesseur pour les points de vie de l'objet représentant le vaisseau.
                @return Les points de vie de l'objet représentant le vaisseau.
                */
                int getPVObj() const;
                /**

                @brief Accesseur pour le type de l'objet représentant le vaisseau.
                @return Le type de l'objet représentant le vaisseau.
                */
                int getTypeObj() const;
                /**

                @brief Accesseur pour la cadence de tir du vaisseau.
                @return La cadence de tir du vaisseau.
                */
                float getCad() const;
                /**

                @brief Accesseur pour la possibilité de tirer du vaisseau.
                @return La possibilité de tirer du vaisseau.
                */
                int getPeutTirer() const;
                /**

                @brief Accesseur pour savoir si l'objet représentant le vaisseau a été détruit.
                @return True si l'objet représentant le vaisseau a été détruit, false sinon.
                */
                bool getDetruitObj() const;

                        //Mutateurs

                /**

                @brief Définit l'objet du vaisseau.
                @param o L'objet à définir.
                */
                void setObj(const Objet& o);
                /**

                @brief Définit la position de l'objet du vaisseau.
                @param Pos La position à définir.
                */
                void setPosObj(const Vec2& Pos);
                /**

                @brief Définit la vitesse de l'objet du vaisseau.
                @param Vit La vitesse à définir.
                */
                void setVitObj(const Vec2& Vit);
                /**

                @brief Définit l'accélération de l'objet du vaisseau.
                @param Acc L'accélération à définir.
                */
                void setAccObj(const Vec2& Acc);
                /**

                @brief Définit la masse de l'objet du vaisseau.
                @param Masse La masse à définir.
                */
                void setMasseObj(const float& Masse);
                /**

                @brief Définit l'échelle de la vitesse de l'objet du vaisseau.
                @param Vscal L'échelle de la vitesse à définir.
                */
                void setVscalObj(const float& Vscal);
                /**

                @brief Définit la taille de l'objet du vaisseau.
                @param Taille La taille à définir.
                */
                void setTailleObj(const float& Taille);
                /**

                @brief Définit l'angle de position de l'objet du vaisseau.
                @param PosAng L'angle de position à définir.
                */
                void setPosAngObj(float PosAng);
                /**

                @brief Définit l'angle de vitesse de l'objet du vaisseau.
                @param VitAng L'angle de vitesse à définir.
                */
                void setVitAngObj(const float& VitAng);
                /**

                @brief Définit les points de vie de l'objet du vaisseau.
                @param PV Les points de vie à définir.
                */
                void setPVObj(const int& PV);
                /**

                @brief Définit le type de l'objet du vaisseau.
                @param Type Le type à définir.
                */
                void setTypeObj(const int& Type);
                /**

                @brief Définit la cadence de tir du vaisseau.
                @param Cad La cadence de tir à définir.
                */
                void setCad(const float& Cad);
                /**

                @brief Définit la possibilité de tirer du vaisseau.
                @param PT La possibilité de tirer à définir.
                */
                void setPeutTirer(const int& PT);
                /**

                @brief Définit l'état de destruction de l'objet du vaisseau.
                @param Detruit L'état de destruction à définir.
                */
                void setDetruitObj(const bool& Detruit);


                        //fonctions
                /**

                @brief Vérifie s'il y a une collision entre le vaisseau et un objet extérieur.
                @param ObjEtr L'objet extérieur avec lequel tester la collision.
                */
                void testCollision(Objet& ObjEtr);
                /**

                @brief Accélère le vaisseau en fonction de son indice d'accélération.
                */
                void accelerer();
                /**

                @brief Recule le vaisseau.
                */
                void reculax();
                /**

                @brief Tourne le vaisseau vers la gauche.
                */
                void tournerGauche();
                /**

                @brief Tourne le vaisseau vers la droite.
                */
                void tournerDroite();
                /**

                @brief Fait tirer le vaisseau.
                */
                void tirer();
                /**

                @brief Effectue un test de régression.
                */
                void testRegression();
};


#endif