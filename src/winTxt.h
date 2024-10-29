#ifndef WINTXT_H
#define WINTXT_H

//! \brief Classe représentant une fenêtre texte en mode console
class WinTXT
{
private:

    int dimx;       //!< \brief Largeur de la fenêtre
    int dimy;       //!< \brief Hauteur de la fenêtre
    char* win;      //!< \brief Stocke le contenu de la fenêtre dans un tableau 1D mais on y accède en 2D

public:

    //! \brief Constructeur de la classe
    //! \param dx Largeur de la fenêtre
    //! \param dy Hauteur de la fenêtre
    WinTXT(int dx, int dy);

    //! \brief Efface la fenêtre avec un caractère spécifié (par défaut ' ')
    //! \param c Caractère utilisé pour l'effacement
    void clear(char c = ' ');

    //! \brief Affiche un caractère à une position spécifiée dans la fenêtre
    //! \param x Coordonnée horizontale
    //! \param y Coordonnée verticale
    //! \param c Caractère à afficher
    void print(int x, int y, char c);

    //! \brief Affiche une chaîne de caractères à une position spécifiée dans la fenêtre
    //! \param x Coordonnée horizontale
    //! \param y Coordonnée verticale
    //! \param c Chaîne de caractères à afficher
    void print(int x, int y, char* c);

    //! \brief Dessine la fenêtre sur la sortie standard (console)
    //! \param x Coordonnée horizontale de la fenêtre dans la console (par défaut 0)
    //! \param y Coordonnée verticale de la fenêtre dans la console (par défaut 0)
    void draw(int x = 0, int y = 0);

    //! \brief Met en pause le programme jusqu'à ce qu'une touche soit pressée
    void pause();

    //! \brief Récupère le caractère pressé par l'utilisateur
    char getCh();

};

//! \brief Efface la console
void termClear();

#endif