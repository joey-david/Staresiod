#include "PowerUp.h"

PowerUp::PowerUp(int Type, int CD, Vec2 Pos, float Taille, bool Actif, int CDActif):
    type(Type), cd(CD),pos(Pos), taille(Taille), actif(Actif), cdActif(CDActif) {}

int PowerUp::getType() const {
    return type;
}

int PowerUp::getCD() const {
    return cd;
}

Vec2 PowerUp::getPos() const {
    return pos;
}

float PowerUp::getTaille() const {
    return taille;
}

bool PowerUp::getActif() const {
    return actif;
}

int PowerUp::getCDActif() const {
    return cdActif;
}

bool PowerUp::getActivation() const {
    return activation;
}

void PowerUp::setType(const int& Type) {
    type = Type;
}

void PowerUp::setCD(const int& CD) {
    cd = CD;
}

void PowerUp::setPos(const Vec2& Pos) {
    pos = Pos;
}

void PowerUp::setTaille(const float& Taille) {
    taille = Taille;
}

void PowerUp::setActif(const bool& Actif) {
    actif = Actif;
}

void PowerUp::setCDActif(const int& CDActif) {
    cdActif = CDActif;
}

void PowerUp::setActivation(const bool& Activation) {
    activation = Activation;
}

void PowerUp::test() {
    PowerUp powerUp(1, 5, Vec2(10.0, 20.0), 1.5, false, 0);
    assert(powerUp.getType() == 1);
    assert(powerUp.getCD() == 5);
    assert(powerUp.getPos().getX() == 10.0 && powerUp.getPos().getY() == 20.0);
    assert(powerUp.getTaille() == 1.5);
    assert(powerUp.getActif() == false);
    assert(powerUp.getCDActif() == 0);
    
    powerUp.setType(2);
    assert(powerUp.getType() == 2);
    powerUp.setCD(3);
    assert(powerUp.getCD() == 3);
    powerUp.setPos(Vec2(5.0, 5.0));
    assert(powerUp.getPos().getX() == 5.0 && powerUp.getPos().getY() == 5.0);
    powerUp.setTaille(2.0);
    assert(powerUp.getTaille() == 2.0);
    powerUp.setActif(true);
    assert(powerUp.getActif() == true);
    powerUp.setCDActif(10);
    assert(powerUp.getCDActif() == 10);
    powerUp.setActivation(true);
    assert(powerUp.getActivation() == true);

    cout << "succès du test de PowerUp." << endl;
}
