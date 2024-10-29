#include "JeuEnTxt.h"
#include "txtJeu.h"
#include "winTxt.h"

int main(int argc, char** argv) {
    termClear();
        JeuEnTxt jeuEnTxt;
        txtBoucle(jeuEnTxt);
    termClear();
    return 0;
}