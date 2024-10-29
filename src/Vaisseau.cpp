#include "Vaisseau.h"
#include <math.h>

Vaisseau::Vaisseau(Vec2 Pos, Vec2 Vit, Vec2 Acc,float Masse, float Vscal,
       float Taille, float PosAng, float VitAng, float AccAng, int PV,
        int Type, float CadenceTir, int PeutTirer, float Indice_acc) :
        o(Pos,Vit,Acc,Masse,Vscal,Taille,PosAng,VitAng,AccAng,PV, Type),
        cadenceTir(CadenceTir),peutTirer(PeutTirer), indice_acc(Indice_acc) {}

Objet Vaisseau::getObj() const {
    return o;
}

Vec2 Vaisseau::getPosObj() const {
    return (o.getPos());
}

Vec2 Vaisseau::getVitObj() const {
    return (o.getVit());

}
Vec2 Vaisseau::getAccObj() const {
    return (o.getAcc());
}

float Vaisseau::getMasseObj() const {
    return(o.getMasse());
}

float Vaisseau::getVscalObj() const {
    return(o.getVscal());
}

float Vaisseau::getTailleObj()  const {
    return(o.getTaille());
}

float Vaisseau::getVitAngObj() const {
    return(o.getVitAng());
}

float Vaisseau::getPosAngObj() const {
    return(o.getPosAng());
}

int Vaisseau::getPVObj() const {
    return o.getPV();
}

int Vaisseau::getTypeObj() const {
    return o.getType();
}

float Vaisseau::getCad() const {
    return cadenceTir;
}

int Vaisseau::getPeutTirer() const {
    return peutTirer;
}

bool Vaisseau::getDetruitObj() const{
    return o.getDetruit();
}

void Vaisseau::setObj(const Objet& obj) {
    o = obj;
}

void Vaisseau::setPosObj(const Vec2& Pos) {
    o.setPos(Pos);
}

void Vaisseau::setVitObj(const Vec2& Vit) {
    o.setVit(Vit);
}

void Vaisseau::setAccObj(const Vec2& Acc) {
    o.setAcc(Acc);
}

void Vaisseau::setMasseObj(const float& Masse) {
    o.setMasse(Masse);
}

void Vaisseau::setVscalObj(const float& Vscal) {
    o.setVscal(Vscal);
}

void Vaisseau::setTailleObj(const float& Taille) {
    o.setTaille(Taille);
}

void Vaisseau::setPosAngObj(float PosAng) {
    o.setPosAng(PosAng);
}

void Vaisseau::setVitAngObj(const float& VitAng) {
    o.setVitAng(VitAng);
}

void Vaisseau::setPVObj(const int& PV) {
    o.setPV(PV);
}

void Vaisseau::setTypeObj(const int& Type) {
    o.setType(Type);
}

void Vaisseau::setCad(const float& Cad) {
    cadenceTir = Cad;
}

void Vaisseau::setPeutTirer(const int& PT) {
    peutTirer = PT;
}

void Vaisseau::setDetruitObj(const bool& Detruit) {
    o.setDetruit(Detruit);
}

void Vaisseau::testCollision(Objet& ObjEtr) {
    o.testCollision(ObjEtr);
}

void Vaisseau::accelerer() {
    float rad = getPosAngObj();
    float x = cos(rad) * 0.5;
    float y = sin(rad) * 0.5;
    Vec2 newAcc(x, y);
    setAccObj(newAcc);
}    

void Vaisseau::reculax() {
    float rad = getPosAngObj();
    float x = -cos(rad) * 0.5;
    float y = -sin(rad) * 0.5;
    Vec2 newAcc(x, y);
    setAccObj(newAcc);
}    

void Vaisseau::tournerGauche() {
    setVitAngObj(getVitAngObj()-0.05);
}

void Vaisseau::tournerDroite() {
    setVitAngObj(getVitAngObj()+0.05);
}

void Vaisseau::tirer() {
    if(getPeutTirer()>0) {
        return;
    }
    else {
        Objet proj;
        proj.setTaille(5);
        proj.setType(1);
        const float VIT_PROJ = 2.0;
        proj.setPos(getPosObj()+Vec2(cos(getPosAngObj())*(getTailleObj()+proj.getTaille()),
            sin(getPosAngObj())*(getTailleObj()+proj.getTaille())));
        proj.setVit(Vec2(cos(getPosAngObj())*VIT_PROJ, 
            sin(getPosAngObj())*VIT_PROJ));
        proj.setPosAng(getPosAngObj());
        projectiles.push_back(proj);
        setPeutTirer(10);
    }
    
}

void Vaisseau::testRegression() {
    Vec2 pos(1, 2);
    setPosObj(pos);
    assert(getPosObj() == pos);

    Vec2 vit(3, 4);
    setVitObj(vit);
    assert(getVitObj() == vit);

    Vec2 acc(5, 6);
    setAccObj(acc);
    assert(getAccObj() == acc);

    float masse = 7.0;
    setMasseObj(masse);
    assert(getMasseObj() == masse);

    float taille = 9.0;
    setTailleObj(taille);
    assert(getTailleObj() == taille);


    float vitAng = 11.0;
    setVitAngObj(vitAng);
    assert(getVitAngObj() == vitAng);

    int PV = 13;
    setPVObj(PV);
    assert(getPVObj() == PV);

    float cadenceTir = 14.0;
    setCad(cadenceTir);
    assert(getCad() == cadenceTir);

    int peutTirer = 0;
    setPeutTirer(peutTirer);
    assert(getPeutTirer() == peutTirer);

    // Tester la méthode tirer()
    int nbProjAvantTir = projectiles.size();
    tirer();
    assert((int)projectiles.size() == nbProjAvantTir + 1);

    cout << "test de regression de vaisseau : ok" << endl;
}
