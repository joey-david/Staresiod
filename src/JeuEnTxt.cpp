#include "JeuEnTxt.h"
#include <fstream>
#include <string>


JeuEnTxt::JeuEnTxt() {
    srand( (unsigned int)time(NULL));
    t.setDimX(25);
    t.setDimY(25);
    v.setPosObj(Vec2(t.getDimX()/2,t.getDimY()/2));
    v.setTailleObj(1);
    score = 0;
    int i;
    nb_aster = 3;
    for (i=0; i<nb_aster; i++) {
        genereAster();
    }
}


void JeuEnTxt::init() const {
}


void JeuEnTxt::genereAster() {
    Objet aster;
    float scaleVitAster = 1;
    float scaleVitAngAster = 1.5;
    aster.setPV(rand()%5+1);
    aster.setType(2);
    aster.setTaille(1*aster.getPV());
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
            aster.setVit(Vec2(scaleVitAster*(rand()%25)/(aster.getTaille()/100),
            scaleVitAster*(rand()%50-25)/(aster.getTaille()/100)));
        } while(aster.getVit()==Vec2(0,0));
    } else if (x == t.getDimX()+s) {
        do {
            aster.setVit(Vec2(scaleVitAster*(rand()%25-25)/(aster.getTaille()/100),
            scaleVitAster*(rand()%50-25)/(aster.getTaille()/100)));
        } while(aster.getVit()==Vec2(0,0));
    } else if (y == -s) {
        do {
            aster.setVit(Vec2(scaleVitAster*(rand()%50-25)/(aster.getTaille()/100),
            scaleVitAster*(rand()%25)/(aster.getTaille()/100)));
        } while(aster.getVit()==Vec2(0,0));
    } else if (y == t.getDimY()+s){
        do {
            aster.setVit(Vec2(scaleVitAster*(rand()%50-25)/(aster.getTaille()/100),
            scaleVitAster*(rand()%25-25)/(aster.getTaille()/100)));
        } while(aster.getVit()==Vec2(0,0));
    }

    aster.setVitAng(scaleVitAngAster*float(rand()%100-5)/(2*aster.getTaille()));
    asteroides.push_back(aster);
}


void JeuEnTxt::update() {
    getUpdate();
    setUpdate();
}


void JeuEnTxt::getUpdate() {
    collisionnage();
    getUpdateVaiss();
    getUpdateAster();
}


/*check les collisions de tous les objets du tableau avec tous les objets du
tableau, sauf eux-mêmes*/
void JeuEnTxt::collisionnage(){

    
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


void JeuEnTxt::getUpdateVaiss() {
    if (v.getPVObj() <= 0){//update du vaisseau, PV et position.
        cout<<"perdu :)"<<endl;
    }
    for(int i = 0; i<(int)v.projectiles.size(); i++){ //update des projectiles
        if (v.projectiles[i].getPV() <= 0 || v.projectiles[i].getPos().getX()>t.getDimX()
            || v.projectiles[i].getPos().getX()<0 || v.projectiles[i].getPos().getY()>t.getDimY()
            || v.projectiles[i].getPos().getY()<0) {
            v.projectiles.erase(v.projectiles.begin()+i);
            }

    }
}


void JeuEnTxt::getUpdateAster() {
    for(int i = 0; i<(int)asteroides.size(); i++){
        if (asteroides[i].getPV() <= 0){
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



void JeuEnTxt::setUpdate() {
    setUpdateAster();
    setUpdateVaiss();
}





void JeuEnTxt::setUpdateAster() {
    const float vmax = 0.5;
    const float scaleVitPos = 0.2;   
    for(int i = 0; i<(int)asteroides.size();i++) {
        float vit_x = asteroides[i].getVit().getX();
        float vit_y = asteroides[i].getVit().getY();
        float vitesse = sqrt(pow(vit_x,2)+pow(vit_y,2));
        if(vitesse>vmax) {
            asteroides[i].setVit(Vec2(vit_x/(vitesse/vmax),vit_y/(vitesse/vmax)));
        }
        asteroides[i].setPos(asteroides[i].getPos()+asteroides[i].getVit()*scaleVitPos);
    }
    if ((int)asteroides.size()<nb_aster) {
        while((int)asteroides.size()<nb_aster) {
            genereAster();
        }
    }

}


void JeuEnTxt::actionClavier (const char touche) {
	switch(touche) {
		case 'z' :
			v.accelerer();
			break;
		case 's' :
			v.reculax();
			break;
		case 'q' :
			v.tournerGauche();
			break;
		case 'd' :
			v.tournerDroite();
			break;
        case 'v' :
            v.tirer();
            break;
	}
}


void JeuEnTxt::setUpdateVaiss() {
    //on vérifie que le vaisseau ne dépasse pas une certain vitesse
    const float vmax = 2.0;    
    const float scaleVitPos = 0.15;
    const float scaleAccVit = 0.2;
    float vit_x = v.getVitObj().getX();
    float vit_y = v.getVitObj().getY();
    float vitesse = sqrt(pow(vit_x,2)+pow(vit_y,2));
    //si c'est le cas, on réduit sa vitesse à la vitesse max
    if(vitesse>vmax) {
        v.setVitObj(Vec2(vit_x/(vitesse/vmax),vit_y/(vitesse/vmax)));
    }
    //update pos et vit vaisseau
    v.setPosObj(v.getPosObj()+v.getVitObj()*scaleVitPos);
    v.setVitObj(v.getVitObj()*(0.98-(vitesse/vmax)/10)+v.getAccObj()*scaleAccVit);
    v.setAccObj(v.getAccObj()*0.9);
    v.setPosAngObj(v.getPosAngObj()+v.getVitAngObj());
    if (abs(v.getVitAngObj()) <= 0.0004) v.setVitAngObj(0);
    else v.setVitAngObj(v.getVitAngObj()*0.9);
    

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
        v.projectiles[i].setPos(v.projectiles[i].getPos()+v.projectiles[i].getVit()*scaleVitPos);
    }
    v.setPeutTirer(v.getPeutTirer()-1);
}


void JeuEnTxt::saveScore() const {
    string filename = "highscore.txt";
    // Check if file exists, create it if not
    ifstream infile(filename);
    if (!infile.good()) {
        ofstream outfile(filename);
        outfile << 0;
    }

    // Récupération du high Score
    string line, previousScore;
    infile.open(filename);
    getline(infile,previousScore);
    infile.close();
    
    // Modification du high score
    ofstream outfile(filename, ios::app);
    if (outfile.good() && score >= stoi(previousScore)) {
        outfile << score;
        outfile.close();
    }}


void JeuEnTxt::exit() {
    assert(1==2);
}

void JeuEnTxt::testRegression() {
    JeuEnTxt j;
    assert(j.asteroides.size() == 3);
    assert(j.score == 0);
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
    cout << "succès du testRegression de JeuEnTxt" << endl;
}
