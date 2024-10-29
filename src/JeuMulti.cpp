#include "JeuMulti.h"
#include <fstream>
#include <string>


JeuMulti::JeuMulti() {
    srand((unsigned int)time(NULL));
    v.setPosObj(Vec2(t.getDimX()/4,t.getDimY()/2));
    w.setPosObj(Vec2(3*(t.getDimX())/4,t.getDimY()/2));
    v.setPosAngObj(M_PI);
    scoreV = 0;
    scoreW = 0;
    int i;
    nb_aster = 10;
    for (i=0; i<nb_aster; i++) {
        genereAster();
    }
    p.setTaille(50.0);
    p.setCDActif(0);
    vmax = 30.0;
    elapsed_frames = 0;
    PU = -1;
}


void JeuMulti::genereAster() {
    Objet aster;
    float scaleVitAster = 2.0;
    float scaleVitAngAster = 1.5;
    aster.setPV(rand()%5+1);
    aster.setType(2);
    aster.setTaille(20*aster.getPV());
    int s = aster.getTaille();
    int s2 = 2*s;
    int x,y;
    bool superposition = true;
    do {
        if(rand()%2==0) {
            //spawn aléatoirement en haut ou en bas
            x = rand()%2 * (t.getDimX()+s2) - s;
            y = rand()%(t.getDimY()+s2) - s;
        }
        else {
            //spawn aléatoirement à gauche ou à droite
            x = rand()%(t.getDimX()+s2) - s;
            y = rand()%2 * (t.getDimY()+s2) - s;

        }
        aster.setPos(Vec2(x, y));
        superposition = false;
        for (int i = 0; i < (int)asteroides.size(); i++) {
            Vec2 dist;
            dist.setX(aster.getPos().getX() - asteroides[i].getPos().getX());
            dist.setY(aster.getPos().getY() - asteroides[i].getPos().getY());
            double distance = sqrt(dist.getX() * dist.getX() + dist.getY() * dist.getY());
            if (distance < aster.getTaille() + asteroides[i].getTaille()) {
                superposition = true;
            }
        }
    } while(superposition);

    if(x == -s) {
        do {
            aster.setVit(Vec2(scaleVitAster*(rand()%25)/(aster.getTaille()/10),
            scaleVitAster*(rand()%50-25)/(aster.getTaille()/10)));
        } while(aster.getVit()==Vec2(0,0));
    } else if (x == t.getDimX()+s) {
        do {
            aster.setVit(Vec2(scaleVitAster*(rand()%25-25)/(aster.getTaille()/10),
            scaleVitAster*(rand()%50-25)/(aster.getTaille()/10)));
        } while(aster.getVit()==Vec2(0,0));
    } else if (y == -s) {
        do {
            aster.setVit(Vec2(scaleVitAster*(rand()%50-25)/(aster.getTaille()/10),
            scaleVitAster*(rand()%25)/(aster.getTaille()/10)));
        } while(aster.getVit()==Vec2(0,0));
    } else if (y == t.getDimY()+s){
        do {
            aster.setVit(Vec2(scaleVitAster*(rand()%50-25)/(aster.getTaille()/10),
            scaleVitAster*(rand()%25-25)/(aster.getTaille()/10)));
        } while(aster.getVit()==Vec2(0,0));
    }

    aster.setVitAng(scaleVitAngAster*float(rand()%10-5)/(2*aster.getTaille()));
    asteroides.push_back(aster);
}


void JeuMulti::update() {
    getUpdate();
    setUpdate();
}


void JeuMulti::getUpdate() {
    collisionnage();
    getUpdateVaiss();
    getUpdateAster();
}


/*check les collisions du vaisseau avec les asteroides, des projectiles avec les 
asteroides et des asteroides entre eux*/
void JeuMulti::collisionnage(){
    if(!(v.getDetruitObj())) {
        Objet wObj = w.getObj();
        v.testCollision(wObj);
        w.setObj(wObj);
    }
    
    for(int i=0; i<(int)asteroides.size(); i++) {
        if (!(v.getDetruitObj())) {
            v.testCollision(asteroides[i]);
            if (asteroides[i].getPV()<=0 && !(asteroides[i].getDetruit())) {
                scoreV+=asteroides[i].getTaille();
                asteroides[i].setDetruit(true);
            }
        }
    }

    for(int i=0; i<(int)asteroides.size(); i++) {
        if (!(w.getDetruitObj())) {
            w.testCollision(asteroides[i]);
            if (asteroides[i].getPV()<=0 && !(asteroides[i].getDetruit())) {
                scoreW+=asteroides[i].getTaille();
                asteroides[i].setDetruit(true);
            }
        }
        
    }


    //tests de collisions pour les proj de vaisseau v
    vector<Objet> tab_obj;
    for(int i=0; i<(int)v.projectiles.size(); i++) {
        tab_obj.push_back(v.projectiles[i]);
    }
    for(int i=0; i<nb_aster; i++) {
        tab_obj.push_back(asteroides[i]);
    }
    
    for(int i=0; i<(int)v.projectiles.size(); i++) {
        for(int j=(int)v.projectiles.size(); j<(int)v.projectiles.size()+nb_aster; j++) {
            if (!(v.getDetruitObj())) {
                tab_obj[i].testCollision(tab_obj[j]);
                if(tab_obj[j].getPV()<=0 && tab_obj[i].getType()==1 
                && tab_obj[j].getType()==2) {
                    float distance = sqrt(pow(tab_obj[i].getPos().getX()-
                    tab_obj[j].getPos().getX(),2) + pow(tab_obj[i].getPos().getY()-
                    tab_obj[j].getPos().getY(),2));
                    if (distance <= (tab_obj[i].getTaille()+tab_obj[j].getTaille()) / 2
                    && !(tab_obj[j].getDetruit())) {
                        scoreV+=tab_obj[j].getTaille();
                        tab_obj[j].setDetruit(true);
                    }
                }
            }
        }
    }
    
    for(int i = 0; i<(int)v.projectiles.size(); i++) {
        v.projectiles[i] = tab_obj[i];
    }

    for (int i = 0; i<nb_aster; i++) {
        asteroides[i] = tab_obj[(int)v.projectiles.size()+i];
    }

    //idem pour le vaisseau w
    vector<Objet> tab_obj2;
    for(int i=0; i<(int)w.projectiles.size(); i++) {
        tab_obj2.push_back(w.projectiles[i]);
    }
    for(int i=0; i<nb_aster; i++) {
        tab_obj2.push_back(asteroides[i]);
    }

    for(int i=0; i<(int)w.projectiles.size(); i++) {
        for(int j=(int)w.projectiles.size(); j<(int)w.projectiles.size()+nb_aster; j++) {
            if (!(w.getDetruitObj())) {
                tab_obj2[i].testCollision(tab_obj2[j]);
                if(tab_obj2[j].getPV()<=0 && tab_obj2[i].getType()==1 
                && tab_obj2[j].getType()==2) {
                    float distance = sqrt(pow(tab_obj2[i].getPos().getX()-
                    tab_obj2[j].getPos().getX(),2) + pow(tab_obj2[i].getPos().getY()-
                    tab_obj2[j].getPos().getY(),2));
                    if (distance <= (tab_obj2[i].getTaille()+tab_obj2[j].getTaille()) / 2
                    && !(tab_obj2[j].getDetruit())) {
                        scoreW+=tab_obj2[j].getTaille();
                        tab_obj2[j].setDetruit(true);
                    }
                }
            }
        }    
    }



    for(int i = 0; i<(int)w.projectiles.size(); i++) {
        w.projectiles[i] = tab_obj2[i];
    }

    for (int i = 0; i<nb_aster; i++) {
        asteroides[i] = tab_obj2[(int)w.projectiles.size()+i];
    }
    
    for(int i=0; i<nb_aster; i++) {
        for (int j = i+1; j<nb_aster; j++) {
            asteroides[i].testCollision(asteroides[j]);
        }
    }

    //test de collision entre vaisseau et projectiles opposés
    for(int i=0; i<(int)w.projectiles.size(); i++) {
        if (!(w.getDetruitObj()))
            v.testCollision(w.projectiles[i]);
    }
    for(int i=0; i<(int)v.projectiles.size(); i++) {
        if (!(v.getDetruitObj()))
            w.testCollision(v.projectiles[i]);
    }
}


void JeuMulti::getUpdateVaiss() {//update des vaisseaux, PV et projectiles.
    if (v.getPVObj() <= 0 && !(v.getDetruitObj())){
        Explosion newExplosion = {int(v.getPosObj().getX()),
        int(v.getPosObj().getY()), 0, 0.5};
        explosions.push_back(newExplosion);
        v.setDetruitObj(true);
    }
    if (w.getPVObj() <= 0 && !(w.getDetruitObj())){
        Explosion newExplosion = {int(w.getPosObj().getX()),
        int(w.getPosObj().getY()), 0, 0.5};
        explosions.push_back(newExplosion);
        w.setDetruitObj(true);
    }
    for(int i = 0; i<(int)v.projectiles.size(); i++){ //update des projectiles
        if(p.getCDActif()>0 && p.getType()==4)
            v.projectiles[i].setPV(100000);
        if (v.projectiles[i].getPV() <= 0 || v.projectiles[i].getPos().getX()>t.getDimX()
            || v.projectiles[i].getPos().getX()<0 || v.projectiles[i].getPos().getY()>t.getDimY()
            || v.projectiles[i].getPos().getY()<0) {
            v.projectiles.erase(v.projectiles.begin()+i);
            }
    }
    for(int i = 0; i<(int)w.projectiles.size(); i++){ //update des projectiles
        if(p.getCDActif()>0 && p.getType()==4)
            w.projectiles[i].setPV(100000);
        if (w.projectiles[i].getPV() <= 0 || w.projectiles[i].getPos().getX()>t.getDimX()
            || w.projectiles[i].getPos().getX()<0 || w.projectiles[i].getPos().getY()>t.getDimY()
            || w.projectiles[i].getPos().getY()<0) {
            w.projectiles.erase(w.projectiles.begin()+i);
            }
    }
}


void JeuMulti::getUpdateAster() {
    for(int i = 0; i<(int)asteroides.size(); i++){
        if (asteroides[i].getPV() <= 0){
            Explosion newExplosion = {int(asteroides[i].getPos().getX()),
            int(asteroides[i].getPos().getY()), 0, float(0.8+0.2*
                asteroides[i].getTaille()/10.0)};
            explosions.push_back(newExplosion);
            asteroides.erase(asteroides.begin()+i);
        }
        if (asteroides[i].getPos().getX()> t.getDimX() + asteroides[i].getTaille()
            || asteroides[i].getPos().getX()<0 - asteroides[i].getTaille() 
            || asteroides[i].getPos().getY()> t.getDimY() + asteroides[i].getTaille()
            || asteroides[i].getPos().getY()<0 - asteroides[i].getTaille()) {
            asteroides.erase(asteroides.begin()+i);
        }
    }
}


void JeuMulti::setUpdate() {
    setUpdateAster();
    setUpdateVaiss();
    setUpdatePowerUp();
    //on fait passer l'affichage des explosions à la frame suivante
    elapsed_frames+=1;
    if (elapsed_frames % 10==0) {
        //augmente le score 3 fois par seconde
        if(!(v.getDetruitObj()))
            scoreV+=1;
        if(!(w.getDetruitObj()))
            scoreW+=1;
    }
}


void JeuMulti::setUpdateAster() {
    const float vmaxA = 2.5;
    const float scaleVitPos = 1;   
    for(int i = 0; i<(int)asteroides.size();i++) {
        float vit_x = asteroides[i].getVit().getX();
        float vit_y = asteroides[i].getVit().getY();
        float vitesse = sqrt(pow(vit_x,2)+pow(vit_y,2));
        if(vitesse>vmaxA) {
            asteroides[i].setVit(Vec2(vit_x/(vitesse/vmaxA),vit_y/(vitesse/vmaxA)));
        }
        asteroides[i].setPos(asteroides[i].getPos()+asteroides[i].getVit()*scaleVitPos);
        asteroides[i].setPosAng(asteroides[i].getPosAng()+asteroides[i].getVitAng());
    }
    if ((int)asteroides.size()<nb_aster) {
        while((int)asteroides.size()<nb_aster) {
            genereAster();
        }
    }

}

void JeuMulti::setUpdatePowerUp() {
    if (p.getActif()) {
        switch (p.getType()) {
            case 1:
                for (int i = 0; i < nb_aster; i++) {
                    asteroides[i].setPV(0);
                }
                break;
            case 2:
                if (p.getCDActif() > 0) {
                    if (PU==0) {
                        v.setPVObj(1000);
                    }
                    else if (PU==1) {
                        w.setPVObj(1000);
                    }
                } 
                break;
            case 3:
                if(p.getCDActif() > 0) {
                    if (PU==0) {
                        v.setVscalObj(2.0);
                    }
                    else if (PU==1) {
                        w.setVscalObj(2.0);
                    }  
                }
                break;
            case 4:
                if (p.getCDActif() > 0) {
                    if (PU==0) {
                        for (int i = 0; i < (int)v.projectiles.size(); i++) {
                            v.projectiles[i].setPV(1000);
                        }
                    } else if (PU==1) {
                        for (int i = 0; i < (int)w.projectiles.size(); i++) {
                            w.projectiles[i].setPV(1000);
                        }
                    }
                }
                break;
            default:
                break;
    }

        p.setActif(false);
    }
    if(p.getCDActif()<0) {
        if (v.getPVObj()>0)
            v.setPVObj(1);
        for(int i = 0; i < (int)v.projectiles.size(); i++){
            if (v.projectiles[i].getPV()>0)
                v.projectiles[i].setPV(1);
        }
        w.setVscalObj(1.0);
        if (w.getPVObj()>0)
            w.setPVObj(1);
        for(int i = 0; i < (int)w.projectiles.size(); i++){
            if (w.projectiles[i].getPV()>0)
                w.projectiles[i].setPV(1);
        }
        w.setVscalObj(1.0);
    }
    if (p.getCD()>0) {
        p.setCD(p.getCD()-1);
    }
    else {
        p.setPos(Vec2(rand()%(t.getDimX()-1),rand()%(t.getDimY()-1)));
        p.setType(rand()%4 + 1);
        p.setCD(600);
        p.setActif(false);
        p.setActivation(true);
        PU = -1;
    }
    p.setCDActif(p.getCDActif()-1);
}


void JeuMulti::actionClavier (set<char>& touches) {
    bool accelerating = (touches.count('z') != 0);
    bool reversing = (touches.count('s') != 0);
    bool turningLeft = (touches.count('q') != 0);
    bool turningRight = (touches.count('d') != 0);
    bool firing = (touches.count('v') != 0);

    if (accelerating) {
        v.accelerer();
        v.indice_acc += 0.05;
    }
    else if (reversing) {
        v.reculax();
        v.indice_acc -= 0.05;
    }
    else v.indice_acc /= 2;
    if (turningLeft) {
        v.tournerGauche();
    }
    if (turningRight) {
        v.tournerDroite();
    }
    if (firing) {
        v.tirer();
    }
    if (v.indice_acc>=2.0) v.indice_acc = 2.0;
    if (v.indice_acc<=-2.0) v.indice_acc = -2.0;
    if (sqrt(pow(v.indice_acc,2)<=0.0005)) v.indice_acc = 0;

    bool acceleratingW = (touches.count('o') != 0);
    bool reversingW = (touches.count('l') != 0);
    bool turningLeftW = (touches.count('k') != 0);
    bool turningRightW = (touches.count('m') != 0);
    bool firingW = (touches.count('p') != 0);

    if (acceleratingW) {
        w.accelerer();
        w.indice_acc += 0.05;
    }
    else if (reversingW) {
        w.reculax();
        w.indice_acc -= 0.05;
    }
    else w.indice_acc /= 2;
    if (turningLeftW) {
        w.tournerGauche();
    }
    if (turningRightW) {
        w.tournerDroite();
    }
    if (firingW) {
        w.tirer();
    }
    if (w.indice_acc>=2.0) w.indice_acc = 2.0;
    if (w.indice_acc<=-2.0) w.indice_acc = -2.0;
    if (sqrt(pow(w.indice_acc,2)<=0.0005)) w.indice_acc = 0;
    
}



void JeuMulti::setUpdateVaiss() {
    //on vérifie que les vaisseaux ne dépassent pas une certain vitesse 
    const float scaleVitPos = 0.8;
    const float scaleAccVit = 2.0;
    float vit_x = v.getVitObj().getX();
    float vit_y = v.getVitObj().getY();
    float vitesse = sqrt(pow(vit_x,2)+pow(vit_y,2));
    float vit_xW = w.getVitObj().getX();
    float vit_yW = w.getVitObj().getY();
    float vitesseW = sqrt(pow(vit_xW,2)+pow(vit_yW,2));
    
    //on réduit la vitesse à la vitesse max
    if(vitesse>vmax) {
        v.setVitObj(Vec2(vit_x/(vitesse/vmax),vit_y/(vitesse/vmax)));
    }
    if(vitesseW>vmax) {
        w.setVitObj(Vec2(vit_xW/(vitesseW/vmax),vit_yW/(vitesseW/vmax)));
    }

    v.setPosAngObj(v.getPosAngObj()+v.getVitAngObj()*0.1);
    if (abs(v.getVitAngObj()) <= 0.001) v.setVitAngObj(0);
    else v.setVitAngObj(v.getVitAngObj()*0.9);

    w.setPosAngObj(w.getPosAngObj()+w.getVitAngObj()*0.1);
    if (abs(w.getVitAngObj()) <= 0.001) w.setVitAngObj(0);
    else w.setVitAngObj(w.getVitAngObj()*0.9);
    
    //update pos et vit vaisseaux
    v.setPosObj(v.getPosObj()+v.getVitObj()*scaleVitPos*v.getVscalObj());
    v.setVitObj((v.getVitObj()*0.9)+v.getAccObj()*scaleAccVit);
    v.setAccObj(v.getAccObj()*0.9);
    w.setPosObj(w.getPosObj()+w.getVitObj()*scaleVitPos*w.getVscalObj());
    w.setVitObj((w.getVitObj()*0.9)+w.getAccObj()*scaleAccVit);
    w.setAccObj(w.getAccObj()*0.9);

    //si les vaisseaux sortent de l'écran, on les ramène de l'autre côté
    if (v.getPosObj().getX()<0) {
        v.setPosObj(Vec2(t.getDimX()+v.getPosObj().getX(),v.getPosObj().getY()));
    }
    if (v.getPosObj().getX()>t.getDimX()) {
        v.setPosObj(Vec2(0+v.getPosObj().getX()-t.getDimX(),v.getPosObj().getY()));
    }
    if (v.getPosObj().getY()<0) {
        v.setPosObj(Vec2(v.getPosObj().getX(),t.getDimY()+v.getPosObj().getY()));
    } 
    if (v.getPosObj().getY()>t.getDimY()) {
        v.setPosObj(Vec2(v.getPosObj().getX(),0+v.getPosObj().getY()-t.getDimY()));
    }
    if (w.getPosObj().getX()<0) {
        w.setPosObj(Vec2(t.getDimX()+w.getPosObj().getX(),w.getPosObj().getY()));
    }
    if (w.getPosObj().getX()>t.getDimX()) {
        w.setPosObj(Vec2(0+w.getPosObj().getX()-t.getDimX(),w.getPosObj().getY()));
    }
    if (w.getPosObj().getY()<0) {
        w.setPosObj(Vec2(w.getPosObj().getX(),t.getDimY()+w.getPosObj().getY()));
    } 
    if (w.getPosObj().getY()>t.getDimY()) {
        w.setPosObj(Vec2(w.getPosObj().getX(),0+w.getPosObj().getY()-t.getDimY()));
    }


    //update pos proj
    for(int i = 0; i < (int)v.projectiles.size(); i++){
        v.projectiles[i].setPos(v.projectiles[i].getPos()+(v.projectiles[i].getVit())*8);
    }
    v.setPeutTirer(v.getPeutTirer()-1);
    for(int i = 0; i < (int)w.projectiles.size(); i++){
        w.projectiles[i].setPos(w.projectiles[i].getPos()+(w.projectiles[i].getVit())*8);
    }
    w.setPeutTirer(w.getPeutTirer()-1);

    //update comparaison avec pos powerup
    float distanceV = sqrt(pow(v.getPosObj().getX()-p.getPos().getX(),2) + 
    pow(v.getPosObj().getY()-p.getPos().getY(),2));

    float distanceW = sqrt(pow(w.getPosObj().getX()-p.getPos().getX(),2) + 
    pow(w.getPosObj().getY()-p.getPos().getY(),2));

    if(distanceV <= (v.getTailleObj()+p.getTaille()) / 2 && p.getActivation() 
        && !v.getDetruitObj()) {
        //activation du power-up
        p.setActif(true);
        p.setCDActif(240);
        p.setActivation(false);
        PU = 0;
    } else if(distanceW <= (w.getTailleObj()+p.getTaille()) / 2 && p.getActivation()
        && !w.getDetruitObj()) {
        //activation du power-up
        p.setActif(true);
        p.setCDActif(240);
        p.setActivation(false);
        PU = 1;
    }

}


void JeuMulti::saveScore() const {
    int BestScore;
    if (scoreV > scoreW) {
        BestScore = scoreV;
    } else {
        BestScore = scoreW;
    }
    string filename = "data/highscore.txt";
    // Vérifie si le fichier existe et le crée sinon
    ifstream infile(filename);
    if (!infile.good()) {
        ofstream outfile(filename);
        outfile << 0;
        outfile.close();
    }
    infile.close();

    // Récupération du high Score
    string line, previousScore;
    infile.open(filename);
    if(getline(infile,previousScore)){
        cout << "Highscore : " << previousScore << endl;
    }
    else {
        cout << "Aucun highscore trouvé. Initialisation à 0" << endl;
        previousScore = "0";
    }
    infile.close();

    // Modification du high score
    ofstream outfile(filename);
    if (outfile.good() && BestScore >= stoi(previousScore)) {
        outfile << BestScore;
    }
    else {
        outfile << previousScore;
    }
    outfile.close();
}



void JeuMulti::exit() {
    assert(1==2);
}

void JeuMulti::testRegression() {
    JeuMulti j;
    assert(j.asteroides.size() == 3);
    assert(j.scoreV == 0);
    assert(j.nb_aster == 3);
    assert(j.v.getPosObj().getX() == j.t.getDimX() / 2);
    assert(j.v.getPosObj().getY() == j.t.getDimY() / 2);
    for (int i = 0; i < j.nb_aster; i++) {
        assert(j.asteroides[i].getPV() >= 1 && j.asteroides[i].getPV() <= 5);
        assert(j.asteroides[i].getTaille() == j.asteroides[i].getPV());
        Vec2 pos = j.asteroides[i].getPos();
        assert(pos.getX() >= 0 && pos.getX() < j.t.getDimX());
        assert(pos.getY() >= 0 && pos.getY() < j.t.getDimY());
        Vec2 vit = j.asteroides[i].getVit();
        assert(vit.getX() >= -2.5 && vit.getX() <= 2.5);
        assert(vit.getY() >= -2.5 && vit.getY() <= 2.5);

    }
    cout << "succès du testRegression de Jeu" << endl;
}
