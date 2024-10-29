/**
@file Objet.h
@brief Définition de la classe Objet, représentant un objet physique dans l'espace.
*/

#ifndef _OBJ
#define _OBJ

#include "Vec2.h"
#include <iostream>
#include <math.h>

using namespace std;

class Objet {
	private:
		Vec2 pos, vit, acc; 									///< Position, vitesse, accélération.
		float masse, vscal, taille, posAng, vitAng, accAng; 	///< Masse, vitesse scalaire, taille, position angulaire, vitesse angulaire, accélération angulaire.
		int pv, type; 											///< Points de vie, type.
		bool detruit; 											///< Booléen indiquant si l'objet a été détruit.
	public:
		/**
		* @brief Constructeur de la classe Objet.
		* @param Pos Vecteur position de l'objet.
		* @param Vit Vecteur vitesse de l'objet.
		* @param Acc Vecteur accélération de l'objet.
		* @param Masse Masse de l'objet.
		* @param Vscal Vitesse scalaire de l'objet.
		* @param Taille Taille de l'objet.
		* @param PosAng Position angulaire de l'objet.
		* @param VitAng Vitesse angulaire de l'objet.
		* @param AccAng Accélération angulaire de l'objet.
		* @param PV Points de vie de l'objet.
		* @param Type Type de l'objet.
		* @param Detruit Booléen indiquant si l'objet a été détruit.
		*/
		Objet(Vec2 Pos = Vec2(0,0), Vec2 Vit = Vec2(0,0), Vec2 Acc = Vec2(0,0),
		float Masse = 0, float Vscal = 0, float Taille = 0, float PosAng = 0,
		float VitAng = 0, float AccAng = 0, int PV = 1, int Type = -1, bool Detruit = false);

		/**
		* @brief Accesseur de la position de l'objet.
		* @return Vecteur position de l'objet.
		*/
		Vec2 getPos() const;

		/**
		* @brief Accesseur de la vitesse de l'objet.
		* @return Vecteur vitesse de l'objet.
		*/
		Vec2 getVit() const;

		/**
		* @brief Accesseur de l'accélération de l'objet.
		* @return Vecteur accélération de l'objet.
		*/
		Vec2 getAcc() const;

		/**
		* @brief Accesseur de la position angulaire de l'objet.
		* @return Position angulaire de l'objet.
		*/
		float getPosAng() const;

		/**
		* @brief Accesseur de la vitesse angulaire de l'objet.
		* @return Vitesse angulaire de l'objet.
		*/
		float getVitAng() const;
			
		/**
		* @brief Accesseur de la masse de l'objet.
		* @return Masse de l'objet.
		*/
		float getMasse() const;

		/**
		* @brief Accesseur de la vitesse scalaire de l'objet.
		* @return Vitesse scalaire de l'objet.
		*/
		float getVscal() const;
		
		/**
		* @brief Retourne la taille de l'objet.
		* 
		* @return float la taille de l'objet.
		*/
		float getTaille() const;

		/**
		 * @brief Retourne le nombre de points de vie de l'objet.
		 * 
		 * @return int le nombre de points de vie de l'objet.
		 */
		int getPV() const;

		/**
		 * @brief Retourne le type de l'objet.
		 * 
		 * @return int le type de l'objet.
		 */
		int getType() const;

		/**
		 * @brief Retourne un booléen indiquant si l'objet est détruit ou non.
		 * 
		 * @return bool true si l'objet est détruit, false sinon.
		 */
		bool getDetruit() const;

		/**
		 * @brief Définit la position de l'objet.
		 * 
		 * @param Pos la nouvelle position de l'objet.
		 */
		void setPos(const Vec2& Pos);

		/**
		 * @brief Définit la vitesse de l'objet.
		 * 
		 * @param Vit la nouvelle vitesse de l'objet.
		 */
		void setVit(const Vec2& Vit);

		/**
		 * @brief Définit l'accélération de l'objet.
		 * 
		 * @param Acc la nouvelle accélération de l'objet.
		 */
		void setAcc(const Vec2& Acc);

		/**
		 * @brief Définit la position angulaire de l'objet.
		 * 
		 * @param PosAng la nouvelle position angulaire de l'objet.
		 */
		void setPosAng(float PosAng);

		/**
		 * @brief Définit la vitesse angulaire de l'objet.
		 * 
		 * @param VitAng la nouvelle vitesse angulaire de l'objet.
		 */
		void setVitAng(const float& VitAng);

		/**
		 * @brief Définit la masse de l'objet.
		 * 
		 * @param Masse la nouvelle masse de l'objet.
		 */
		void setMasse(const float& Masse);

		/**
		 * @brief Définit l'échelle de la vitesse de l'objet.
		 * 
		 * @param Vscal la nouvelle échelle de la vitesse de l'objet.
		 */
		void setVscal(const float& Vscal);

		/**
		 * @brief Définit la taille de l'objet.
		 * 
		 * @param Taille la nouvelle taille de l'objet.
		 */
		void setTaille(const float& Taille);

		/**
		 * @brief Définit le nombre de points de vie de l'objet.
		 * 
		 * @param PV le nouveau nombre de points de vie de l'objet.
		 */
		void setPV(const int& PV);

		/**
		 * @brief Définit le type de l'objet.
		 * 
		 * @param Type le nouveau type de l'objet.
		 */
		void setType(const int& Type);

		/**
		 * @brief Définit si l'objet est détruit ou non.
		 * 
		 * @param Detruit true si l'objet est détruit, false sinon.
		 */
		void setDetruit(const bool& Detruit);

		/**
		 * @brief Vérifie si l'objet entre en collision avec un autre objet.
		 * 
		 * @param ObjEtr l'objet avec lequel on teste la collision.
		 */
		void testCollision(Objet& ObjEtr);

		/**

		@brief Lance un test de regression sur l'objet.
		Cette fonction permet de tester les différentes fonctionnalités de l'objet et d'assurer son bon fonctionnement.
		*/
		void testRegression();
};

#endif