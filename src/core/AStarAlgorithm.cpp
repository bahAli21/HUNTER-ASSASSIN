
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
