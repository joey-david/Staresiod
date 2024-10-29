#include "Terrain.h"

Terrain::Terrain(int DimX, int DimY) : dimx(DimX), dimy(DimY) {}

int Terrain::getDimX() const {
    return dimx;
}

int Terrain::getDimY() const {
    return dimy;
}

void Terrain::setDimX(const int& DimX) {
    dimx = DimX;
}

void Terrain::setDimY(const int& DimY) {
    dimy = DimY;
}
