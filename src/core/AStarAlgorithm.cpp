
#include "AStarAlgorithm.h"
#include <algorithm>
#include <cmath>

/**
 * @brief Utilisation de l'espace de noms std::placeholders.
 *
 * Cela permet d'utiliser les symboles de l'espace de noms std::placeholders sans les qualifier.
 * std::placeholders contient des symboles spéciaux utilisés avec std::bind pour indiquer
 * les emplacements des paramètres liés à une fonction.
 *
 * Par exemple, _1, _2, ... sont des placeholders qui correspondent aux paramètres de la fonction
 * lors de l'utilisation de std::bind. Ils permettent de spécifier quel argument de la fonction
 * passée à std::bind correspond à quel paramètre de la fonction liée.
 *
 * Cette déclaration permet d'utiliser ces symboles directement dans le code sans les qualifier
 * avec std::placeholders::.
 */
using namespace std::placeholders;

/**
 * @brief Surcharge de l'opérateur d'égalité pour comparer deux objets Vec2i.
 *
 * Cette fonction surcharge l'opérateur d'égalité (==) pour comparer les coordonnées
 * de deux objets Vec2i et retourner true si les coordonnées sont égales, sinon false.
 *
 * @param coordinates_ Les coordonnées à comparer.
 * @return True si les coordonnées sont égales, sinon false.
 */
bool AStar::Vec2i::operator==(const Vec2i& coordinates_)
{
    return (x == coordinates_.x && y == coordinates_.y);
}

/**
 * @brief Constructeur de Node avec paramètres.
 *
 * Ce constructeur initialise un objet Node avec les coordonnées spécifiées et éventuellement
 * un parent (par défaut nullptr). Il initialise également les coûts G et H à zéro.
 *
 * @param coordinates_ Les coordonnées du nœud.
 * @param parent_ Le nœud parent (optionnel, par défaut nullptr).
 */
AStar::Node::Node(Vec2i coordinates_, Node* parent_) : parent(parent_), coordinates(coordinates_)
{
    G = H = 0; // Initialise les coûts G et H à zéro
}

/**
 * @brief Calcule le score du nœud (F = G + H).
 *
 * Cette méthode calcule et retourne le score du nœud, qui est la somme des coûts
 * G (coût du chemin parcouru depuis le nœud initial jusqu'à ce nœud) et H
 * (estimation heuristique du coût restant pour atteindre la destination depuis ce nœud).
 *
 * @return Le score du nœud.
 */
AStar::uint AStar::Node::getScore()
{
    return G + H;
}


/**
 * @brief Constructeur par défaut de la classe Generator.
 *
 * Ce constructeur initialise un nouvel objet Generator avec les paramètres par défaut.
 * Il désactive le mouvement diagonal par défaut et utilise la distance de Manhattan comme heuristique par défaut.
 * De plus, il initialise les directions possibles pour le déplacement dans toutes les directions.
 */
AStar::Generator::Generator()
{
    // Désactive le mouvement diagonal par défaut
    setDiagonalMovement(false);

    // Utilise la distance de Manhattan comme heuristique par défaut
    setHeuristic(&Heuristic::manhattan);

    // Initialise les directions possibles pour le déplacement
    direction = {
            {0, 1},     // Déplacement vers le haut.
            {1, 0},     // Déplacement vers la droite.
            {0, -1},    // Déplacement vers le bas.
            {-1, 0},    // Déplacement vers la gauche.
            {-1, -1},   // Déplacement en diagonale vers le bas à gauche.
            {1, 1},     // Déplacement en diagonale vers le haut à droite.
            {-1, 1},    // Déplacement en diagonale vers le haut à gauche.
            {1, -1}     // Déplacement en diagonale vers le bas à droite.
    };

}

/**
 * @brief Définit la taille du monde dans lequel la recherche de chemin est effectuée.
 *
 * Cette fonction prend les dimensions du monde en entrée et met à jour la variable
 * worldSize de l'objet Generator avec ces dimensions.
 *
 * @param worldSize_ Les dimensions du monde.
 */
void AStar::Generator::setWorldSize(Vec2i worldSize_)
{
    worldSize = worldSize_;
}

/**
 * @brief Active ou désactive le mouvement diagonal.
 *
 * Cette fonction permet d'activer ou de désactiver le mouvement diagonal dans la recherche de chemin.
 * Si enable_ est true, le mouvement diagonal est activé, ce qui signifie qu'il y a 8 directions possibles.
 * Sinon, le mouvement diagonal est désactivé et il n'y a que 4 directions possibles (haut, bas, gauche, droite).
 *
 * @param enable_ True pour autoriser le mouvement diagonal, false sinon.
 */
void AStar::Generator::setDiagonalMovement(bool enable_)
{
    // Met à jour le nombre de directions en fonction de l'activation ou de la désactivation du mouvement diagonal
    directions = (enable_ ? 8 : 4); // ? = true on prends donc 8 case et : = false
}

/**
 * @brief Définit la fonction heuristique utilisée pour estimer le coût restant jusqu'à la destination.
 *
 * Cette fonction permet de définir la fonction heuristique à utiliser dans l'algorithme A* pour estimer le coût restant
 * pour atteindre la destination depuis une position donnée.
 *
 * @param heuristic_ La fonction heuristique à utiliser.
 */
void AStar::Generator::setHeuristic(HeuristicFunction heuristic_)
{
    // Utilise std::bind pour lier la fonction heuristique fournie à la variable heuristic de l'objet Generator
    //heuristic = std::bind(heuristic_, _1, _2);
    heuristic = heuristic_;
}



