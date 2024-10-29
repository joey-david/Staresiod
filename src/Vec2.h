#ifndef _VEC2
#define _VEC2

#include <iostream>
#include <cassert>
using namespace std;

class Vec2 {
    private:
        float x,y;
    public:
        /**
         * @brief Constructeur de la classe Vec2
         * @param X Valeur de l'abscisse du vecteur
         * @param Y Valeur de l'ordonnée du vecteur
         */
        Vec2(float X = 0, float Y = 0);
        
        /**
         * @brief Constructeur de recopie de la classe Vec2
         * @param v Vecteur à recopier
         */
        Vec2(const Vec2& v);
        
        /**
         * @brief Accesseur pour la valeur de l'abscisse du vecteur
         * @return La valeur de l'abscisse du vecteur
         */
        float getX() const;
        
        /**
         * @brief Accesseur pour la valeur de l'ordonnée du vecteur
         * @return La valeur de l'ordonnée du vecteur
         */
        float getY() const;
        
        /**
         * @brief Mutateur pour la valeur de l'abscisse du vecteur
         * @param X Nouvelle valeur de l'abscisse du vecteur
         */
        void setX(const float& X);
        
        /**
         * @brief Mutateur pour la valeur de l'ordonnée du vecteur
         * @param Y Nouvelle valeur de l'ordonnée du vecteur
         */
        void setY(const float& Y);
        
        /**
         * @brief Surcharge de l'opérateur d'addition de deux vecteurs
         * @param v Vecteur à ajouter à l'objet courant
         * @return Le résultat de l'addition des deux vecteurs
         */
        Vec2 operator+(Vec2 v);
        
        /**
         * @brief Surcharge de l'opérateur de soustraction de deux vecteurs
         * @param v Vecteur à soustraire à l'objet courant
         * @return Le résultat de la soustraction des deux vecteurs
         */
        Vec2 operator-(Vec2& v);
        
        /**
         * @brief Surcharge de l'opérateur de multiplication de deux vecteurs
         * @param v Vecteur à multiplier à l'objet courant
         * @return Le résultat de la multiplication des deux vecteurs
         */
        Vec2 operator*(Vec2& v);
        
        /**
         * @brief Surcharge de l'opérateur de multiplication d'un vecteur par un scalaire
         * @param lambda Scalaire à multiplier au vecteur courant
         * @return Le résultat de la multiplication du vecteur courant par le scalaire lambda
         */
        Vec2 operator*(float lambda);
        
        /**
         * @brief Surcharge de l'opérateur d'égalité de deux vecteurs
         * @param v Vecteur à comparer à l'objet courant
         * @return Vrai si les deux vecteurs sont égaux, faux sinon
         */
        bool operator==(Vec2 v);
        
        /**
         * @brief Fonction de test de la classe Vec2
         * Affiche les valeurs des attributs x et y du vecteur courant
         */
        void test();
};

#endif