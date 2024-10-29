/**
@file Terrain.h
@brief Déclaration de la classe Terrain et de ses fonctions membres.
*/
#ifndef _TER
#define _TER

#include <iostream>

/**

@class Terrain

@brief Classe représentant le terrain.

Un terrain est défini par une dimension en x et en y.
*/
class Terrain {
	private:
		int dimx, dimy; /** Les dimensions du terrain. */
	public:
		/**
		* @brief Constructeur de la classe Terrain.
		* @param DimX La dimension en x du terrain.
		* @param DimY La dimension en y du terrain.
		*/
		Terrain(int DimX = 750, int DimY = 750);
		/**
		* @brief Accesseur de la dimension en x du terrain.
		* @return La dimension en x du terrain.
		*/
		int getDimX() const;

		/**
		* @brief Accesseur de la dimension en y du terrain.
		* @return La dimension en y du terrain.
		*/
		int getDimY() const;

		/**
		* @brief Mutateur de la dimension en x du terrain.
		* @param DimX La nouvelle dimension en x du terrain.
		*/
		void setDimX(const int& DimX);

		/**
		* @brief Mutateur de la dimension en y du terrain.
		* @param DimY La nouvelle dimension en y du terrain.
		*/
		void setDimY(const int& DimY);

};


#endif