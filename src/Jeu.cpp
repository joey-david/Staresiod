#include "Jeu.h"
#include <fstream>
#include <string>


Jeu::Jeu() {
    srand( (unsigned int)time(NULL));
    v.setPosObj(Vec2(t.getDimX()/2,t.getDimY()/2));
    score = 0;
    int i;
    nb_aster = 10;
    for (i=0; i<nb_aster; i++) {
        genereAster();
    }
    p.setTaille(50.0);
    p.setCDActif(0);
    vmax = 30.0;
    elapsed_frames = 0;
}


void Jeu::genereAster() {
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


void Jeu::update() {
    getUpdate();
    setUpdate();
}


void Jeu::getUpdate() {
    collisionnage();
    getUpdateVaiss();
    getUpdateAster();
}


/*check les collisions du vaisseau avec les asteroides, des projectiles avec les 
asteroides et des asteroides entre eux*/
void Jeu::collisionnage(){

    
    for(int i=0; i<(int)asteroides.size(); i++) {
        v.testCollision(asteroides[i]);
        if (asteroides[i].getPV()<=0 && !(asteroides[i].getDetruit())) {
                score+=asteroides[i].getTaille();
                asteroides[i].setDetruit(true);
        }
    }
    
    vector<Objet> tab_obj;
    for(int i=0; i<(int)v.projectiles.size(); i++) {
        tab_obj.push_back(v.projectiles[i]);
    }
    for(int i=0; i<nb_aster; i++) {
        tab_obj.push_back(asteroides[i]);
    }
    
    for(int i=0; i<(int)v.projectiles.size(); i++) {
        for(int j=(int)v.projectiles.size(); j<(int)v.projectiles.size()+nb_aster; j++) {
            tab_obj[i].testCollision(tab_obj[j]);
            if(tab_obj[j].getPV()<=0 && tab_obj[i].getType()==1 
            && tab_obj[j].getType()==2) {
                float distance = sqrt(pow(tab_obj[i].getPos().getX()-
                tab_obj[j].getPos().getX(),2) + pow(tab_obj[i].getPos().getY()-
                tab_obj[j].getPos().getY(),2));
                if (distance <= (tab_obj[i].getTaille()+tab_obj[j].getTaille()) / 2
                && !(tab_obj[j].getDetruit())) {
                    score+=tab_obj[j].getTaille();
                    tab_obj[j].setDetruit(true);
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
    
    for(int i=0; i<nb_aster; i++) {
        for (int j = i+1; j<nb_aster; j++) {
            asteroides[i].testCollision(asteroides[j]);
        }
    }
    

}


void Jeu::getUpdateVaiss() {//update du vaisseau, PV et projectiles.
    if (v.getPVObj() <= 0){
        Explosion newExplosion = {int(v.getPosObj().getX()),
        int(v.getPosObj().getY()), 0, 0.5};
        explosions.push_back(newExplosion);
        cout<<"perdu =)"<<endl;
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
}


void Jeu::getUpdateAster() {
    for(int i = 0; i<(int)asteroides.size(); i++){
        if (asteroides[i].getPV() <= 0){
            Explosion newExplosion = {int(asteroides[i].getPos().getX()),
            int(asteroides[i].getPos().getY()), 0, float(0.8+0.2*
                asteroides[i].getTaille()/10)};
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


void Jeu::setUpdate() {
    setUpdateAster();
    setUpdateVaiss();
    setUpdatePowerUp();
    //on fait passer l'affichage des explosions à la frame suivante
    elapsed_frames+=1;
    if (elapsed_frames % 10==0)
    //augmente le score 3 fois par seconde
        score+=1;
}


void Jeu::setUpdateAster() {
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

void Jeu::setUpdatePowerUp() {
    if (p.getActif()) {
        switch (p.getType()) {
            case 1:
                for (int i = 0; i < nb_aster; i++) {
                    asteroides[i].setPV(0);
                }
                break;
            case 2:
                if (p.getCDActif() > 0)
                    v.setPVObj(1000);
                break;
            case 3:
                if(p.getCDActif() > 0)
                    v.setVscalObj(2.0);
                break;
            case 4:
                if (p.getCDActif() > 0) {
                    for (int i = 0; i < (int)v.projectiles.size(); i++) {
                        v.projectiles[i].setPV(1000);
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
        v.setVscalObj(1.0);
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
    }
    p.setCDActif(p.getCDActif()-1);
}


void Jeu::actionClavier (set<char>& touches) {
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
    
}



void Jeu::setUpdateVaiss() {
    //on vérifie que le vaisseau ne dépasse pas une certain vitesse 
    const float scaleVitPos = 0.8;
    const float scaleAccVit = 2.0;
    float vit_x = v.getVitObj().getX();
    float vit_y = v.getVitObj().getY();
    float vitesse = sqrt(pow(vit_x,2)+pow(vit_y,2));
    
    //on réduit la vitesse à la vitesse max
    if(vitesse>vmax) {
        v.setVitObj(Vec2(vit_x/(vitesse/vmax),vit_y/(vitesse/vmax)));
    }

    v.setPosAngObj(v.getPosAngObj()+v.getVitAngObj()*0.1);
    if (abs(v.getVitAngObj()) <= 0.001) v.setVitAngObj(0);
    else v.setVitAngObj(v.getVitAngObj()*0.9);
    
    //update pos et vit vaisseau
    v.setPosObj(v.getPosObj()+v.getVitObj()*scaleVitPos*v.getVscalObj());
    v.setVitObj((v.getVitObj()*0.9)+v.getAccObj()*scaleAccVit);
    v.setAccObj(v.getAccObj()*0.9);

    //si le vaisseau sort de l'écran, on le ramène de l'autre côté
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
    
    //update pos proj
    for(int i = 0; i < (int)v.projectiles.size(); i++){
        v.projectiles[i].setPos(v.projectiles[i].getPos()+(v.projectiles[i].getVit())*8);
    }
    v.setPeutTirer(v.getPeutTirer()-1);

    //update comparaison avec pos powerup
    float distance = sqrt(pow(v.getPosObj().getX()-p.getPos().getX(),2) + 
    pow(v.getPosObj().getY()-p.getPos().getY(),2));

    if(distance <= (v.getTailleObj()+p.getTaille()) / 2 && p.getActivation()) {
        //activation du power-up
        p.setActif(true);
        p.setCDActif(240);
        p.setActivation(false);
    }
}


void Jeu::saveScore() const {
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
    if (outfile.good() && score >= stoi(previousScore)) {
        outfile << score;
    }
    else {
        outfile << previousScore;
    }
    outfile.close();
}



void Jeu::exit() {
    assert(1==2);
}

void Jeu::testRegression() {
    Jeu j;
    assert((int)j.asteroides.size() == j.nb_aster);
    assert(j.score == 0);
    assert(j.nb_aster == 10);
    assert(j.v.getPosObj().getX() == j.t.getDimX() / 2);
    assert(j.v.getPosObj().getY() == j.t.getDimY() / 2);
    for (int i = 0; i < j.nb_aster; i++) {
        assert(j.asteroides[i].getPV() >= 1 && j.asteroides[i].getPV() <= 5);
        assert(j.asteroides[i].getTaille() == j.asteroides[i].getPV()*20);
        Vec2 pos = j.asteroides[i].getPos();
        assert(pos.getX() >= -101 && pos.getX() < j.t.getDimX()+101);
        assert(pos.getY() >= -101 && pos.getY() < j.t.getDimY()+101);
        Vec2 vit = j.asteroides[i].getVit();
        assert(vit.getX() >= -25 && vit.getX() <= 25);
        assert(vit.getY() >= -25 && vit.getY() <= 25);

    }
    cout << "test de regression jeu : ok" << endl;
}
