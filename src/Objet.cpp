#include "Objet.h"

Objet::Objet(Vec2 Pos, Vec2 Vit, Vec2 Acc,float Masse, float Vscal,
       float Taille, float PosAng, float VitAng, float AccAng, int PV, int Type,
       bool Detruit) : 
       pos(Pos), vit(Vit), acc(Acc), masse(Masse), vscal(Vscal), taille(Taille),
       posAng(PosAng), vitAng(VitAng), accAng(AccAng), pv(PV), type(Type), 
       detruit(Detruit) {}

Vec2 Objet::getPos() const {
       return pos;
}

Vec2 Objet::getVit() const {
       return vit;
}

Vec2 Objet::getAcc() const {
       return acc;
}

float Objet::getPosAng() const {
       return posAng;
}

float Objet::getVitAng() const {
       return vitAng;
}

float Objet::getMasse() const {
       return masse;
}

float Objet::getVscal() const {
       return vscal;
}

float Objet::getTaille() const {
       return taille;
}

int Objet::getPV() const {
       return pv;
}

int Objet::getType() const {
       return type;
}

bool Objet::getDetruit() const {
       return detruit;
}

void Objet::setPos(const Vec2& Pos) {
       pos = Pos;
}

void Objet::setVit(const Vec2& Vit) {
       vit = Vit;
}

void Objet::setAcc(const Vec2& Acc) {
       acc = Acc;
}

void Objet::setPosAng(float PosAng) {
       if (PosAng>2*M_PI) {
              do {
                     PosAng -= 2*M_PI;
              } while (PosAng>2*M_PI);
       }
       else if (PosAng<0) {
              do {
                     PosAng += 2*M_PI;
              } while (PosAng<0);
       }
       posAng = PosAng;
}

void Objet::setVitAng(const float& VitAng) {
       vitAng = VitAng;
}

void Objet::setMasse(const float& Masse) {
       masse = Masse;
}

void Objet::setVscal(const float& VMax) {
       vscal = VMax;
}

void Objet::setTaille(const float& Taille) {
       taille = Taille;
}

void Objet::setPV(const int& PV) {
       pv = PV;
}

void Objet::setType(const int& Type) {
       type = Type;
}

void Objet::setDetruit(const bool& Detruit) {
       detruit = Detruit;
}

void Objet::testCollision(Objet& ObjEtr) {
    float distance = sqrt(pow(getPos().getX()-ObjEtr.getPos().getX(),2) + 
    pow(getPos().getY()-ObjEtr.getPos().getY(),2));
    if (distance <= (getTaille()+ObjEtr.getTaille()) / 2) {
        int PVact = ObjEtr.getPV();
        ObjEtr.setPV(PVact - getPV());
        setPV(getPV() - PVact);
    }
}


void Objet::testRegression() {
    // test constructor with default values
    Objet o1;
    assert(o1.getPos() == Vec2(0, 0));
    assert(o1.getVit() == Vec2(0, 0));
    assert(o1.getAcc() == Vec2(0, 0));
    assert(o1.getMasse() == 0);
    assert(o1.getTaille() == 0);
    assert(o1.getPosAng() == 0);
    assert(o1.getVitAng() == 0);
    assert(o1.getPV() == 1);

    // test constructor with non-default values
    Objet o2(Vec2(1, 2), Vec2(3, 4), Vec2(5, 6), 7, 8, 9, 10, 11, 12, 13);
    assert(o2.getPos() == Vec2(1, 2));
    assert(o2.getVit() == Vec2(3, 4));
    assert(o2.getAcc() == Vec2(5, 6));
    assert(o2.getMasse() == 7);
    assert(o2.getTaille() == 9);
    assert(o2.getVitAng() == 11);
    assert(o2.getPV() == 13);

    // test mutators and accessors
    Objet o3;
    o3.setPos(Vec2(1, 2));
    assert(o3.getPos() == Vec2(1, 2));
    o3.setVit(Vec2(3, 4));
    assert(o3.getVit() == Vec2(3, 4));
    o3.setAcc(Vec2(5, 6));
    assert(o3.getAcc() == Vec2(5, 6));
    o3.setMasse(7);
    assert(o3.getMasse() == 7);
    o3.setTaille(9);
    assert(o3.getTaille() == 9);
    o3.setVitAng(11);
    assert(o3.getVitAng()==11);
    o3.setPV(13);
    assert(o3.getPV() == 13);
     std::cout<<"test de regression de objet : ok"<<std::endl;
}

