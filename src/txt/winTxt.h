#ifndef WINTXT_H
#define WINTXT_H

/**
 * @brief Une fenêtre texte est un tableau 2D de caractères.
 */
class WinTXT {
private:
    int dimx;   //!< Largeur de la fenêtre.
    int dimy;   //!< Hauteur de la fenêtre.
    char *win;  //!< Stocke le contenu de la fenêtre dans un tableau 1D, mais on y accède en 2D.

public:
    /**
     * @brief Constructeur de la classe WinTXT.
     * @param dx Largeur de la fenêtre.
     * @param dy Hauteur de la fenêtre.
     */
    WinTXT(int dx, int dy);

    /**
     * @brief Efface le contenu de la fenêtre avec le caractère spécifié.
     * @param c Caractère utilisé pour effacer la fenêtre (par défaut, un espace).
     */
    void clear(char c = ' ');

    /**
     * @brief Affiche un caractère à une position spécifique dans la fenêtre.
     * @param x Position horizontale du caractère.
     * @param y Position verticale du caractère.
     * @param c Caractère à afficher.
     */
    void print(int x, int y, char c);

    /**
     * @brief Affiche une chaîne de caractères à une position spécifique dans la fenêtre.
     * @param x Position horizontale du début de la chaîne.
     * @param y Position verticale du début de la chaîne.
     * @param c Pointeur vers la chaîne de caractères à afficher.
     */
    void print(int x, int y, char *c);

    /**
     * @brief Dessine la fenêtre à l'écran, en commençant à la position spécifiée.
     * @param x Position horizontale de départ pour le dessin.
     * @param y Position verticale de départ pour le dessin.
     */
    void draw(int x = 0, int y = 0);

    /**
     * @brief Met en pause le programme jusqu'à ce qu'une touche soit enfoncée.
     */
    void pause();

    /**
     * @brief Obtient un caractère à partir de l'entrée standard.
     * @return Le caractère lu depuis l'entrée standard.
     */
    char getCh();
};

/**
 * @brief Efface le contenu de la console (terminal).
 */
void termClear();

#endif
