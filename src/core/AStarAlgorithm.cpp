
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

/**
         * @brief Ajoute une collision représentée par un rectangle à la liste des obstacles dans le monde.
         *
         * Cette méthode permet d'ajouter un obstacle sous forme de rectangle à la liste des obstacles
         * considérés par l'algorithme A*. Les coordonnées spécifiées représentent le coin supérieur gauche
         * du rectangle obstacle, et la largeur et la hauteur définissent les dimensions du rectangle.
         * Chaque point à l'intérieur du rectangle sera considéré comme une collision par l'algorithme A*.
         *
         * @param topLeft Les coordonnées du coin supérieur gauche du rectangle obstacle.
         * @param width La largeur du rectangle obstacle (par défaut 0).
         * @param height La hauteur du rectangle obstacle (par défaut 0).
         */
void AStar::Generator::addCollision(Vec2i topLeft, int width, int height)
{
    // Ajouter les coordonnées de tous les points du rectangle obstacle à la liste des murs
    for (int x = topLeft.x; x < topLeft.x + width; ++x) {
        for (int y = topLeft.y; y < topLeft.y + height; ++y) {
            walls.push_back({x, y});
        }
    }
}

/**
 * @brief Supprime une collision de la liste des obstacles dans le monde.
 *
 * Cette fonction prend les coordonnées de la collision à supprimer en entrée,
 * recherche ces coordonnées dans la liste walls et les supprime si elles sont trouvées.
 *
 * @param coordinates_ Les coordonnées de la collision à supprimer.
 */
void AStar::Generator::removeCollision(Vec2i coordinates_)
{
    // Recherche la collision à supprimer dans la liste walls
    auto it = std::find(walls.begin(), walls.end(), coordinates_);

    // Si la collision est trouvée, la supprime de la liste
    if (it != walls.end()) {
        walls.erase(it);
    }
}

/**
 * @brief Efface toutes les collisions de la liste des obstacles dans le monde.
 *
 * Cette fonction supprime toutes les collisions de la liste walls de l'objet Generator,
 * effaçant ainsi tous les obstacles dans le monde.
 */
void AStar::Generator::clearCollisions()
{
    walls.clear();
}

/**
 * @brief Recherche un chemin de la source vers la cible en utilisant l'algorithme A*.
 *
 * Cette méthode utilise l'algorithme A* pour trouver un chemin de la source à la cible
 * dans l'environnement donné. Elle prend en compte les obstacles, la taille de la grille,
 * les mouvements diagonaux et une fonction heuristique pour estimer le coût restant.
 *
 * @param source_ Les coordonnées de la source.
 * @param target_ Les coordonnées de la cible.
 * @return Une liste de coordonnées représentant le chemin trouvé de la source à la cible.
 */
AStar::CoordinateList AStar::Generator::findPath(Vec2i source_, Vec2i target_)
{
    Node *current = nullptr; // Nœud actuel dans l'algorithme
    NodeSet openSet, closedSet; // Ensembles de nœuds ouverts et fermés
    openSet.reserve(100); // Réserve de la mémoire pour optimiser les performances
    closedSet.reserve(100); // Réserve de la mémoire pour optimiser les performances
    openSet.push_back(new Node(source_)); // Ajoute le nœud de départ à l'ensemble des nœuds ouverts

    // Tant qu'il y a des nœuds dans l'ensemble des nœuds ouverts
    while (!openSet.empty()) {
        auto current_it = openSet.begin();
        current = *current_it;

        // Recherche du nœud avec le score le plus bas dans l'ensemble des nœuds ouverts
        for (auto it = openSet.begin(); it != openSet.end(); it++) {
            auto node = *it;
            if (node->getScore() <= current->getScore()) {
                current = node;
                current_it = it;
            }
        }

        // Si le nœud actuel correspond à la cible, le chemin est trouvé
        if (current->coordinates == target_) {
            break;
        }

        // Déplace le nœud actuel de l'ensemble des nœuds ouverts à l'ensemble des nœuds fermés
        closedSet.push_back(current);
        openSet.erase(current_it);

        // Parcours des directions possibles pour générer les successeurs du nœud actuel
        for (uint i = 0; i < directions; ++i) {
            Vec2i newCoordinates(current->coordinates + direction[i]);
            if (detectCollision(newCoordinates) ||
                findNodeOnList(closedSet, newCoordinates)) {
                continue; // Si la position est un obstacle ou est déjà évaluée, passe à la suivante
            }

            // Calcul du coût total pour atteindre le successeur
            uint totalCost = current->G + ((i < 4) ? 10 : 14); // Coût 10 pour les déplacements horizontaux/verticaux, 14 pour les diagonales

            // Recherche du successeur dans l'ensemble des nœuds ouverts
            Node *successor = findNodeOnList(openSet, newCoordinates);
            if (successor == nullptr) { // Si le successeur n'existe pas dans l'ensemble des nœuds ouverts
                successor = new Node(newCoordinates, current); // Crée un nouveau nœud
                successor->G = totalCost; // Met à jour le coût G du successeur
                successor->H = heuristic(successor->coordinates, target_); // Calcule et met à jour le coût H du successeur
                openSet.push_back(successor); // Ajoute le successeur à l'ensemble des nœuds ouverts
            }
            else if (totalCost < successor->G) { // Si le coût total pour atteindre le successeur est inférieur à son coût G actuel
                successor->parent = current; // Met à jour le parent du successeur
                successor->G = totalCost; // Met à jour le coût G du successeur
            }
        }
    }

    CoordinateList path; // Chemin trouvé
    while (current != nullptr) { // Reconstitution du chemin en suivant les parents à partir du nœud final
        path.push_back(current->coordinates);
        current = current->parent;
    }

    releaseNodes(openSet); // Libère la mémoire allouée pour les nœuds dans l'ensemble des nœuds ouverts
    releaseNodes(closedSet); // Libère la mémoire allouée pour les nœuds dans l'ensemble des nœuds fermés

    return path; // Retourne le chemin trouvé
}


/**
 * @brief Recherche un nœud dans une liste par ses coordonnées.
 *
 * Cette méthode parcourt une liste de nœuds et recherche un nœud dont les coordonnées
 * correspondent à celles spécifiées. Si un tel nœud est trouvé, un pointeur vers ce nœud
 * est retourné. Sinon, la valeur nullptr est retournée.
 *
 * @param nodes_ La liste de nœuds dans laquelle effectuer la recherche.
 * @param coordinates_ Les coordonnées du nœud à rechercher.
 * @return Un pointeur vers le nœud recherché, ou nullptr s'il n'est pas trouvé.
 */

AStar::Node* AStar::Generator::findNodeOnList(NodeSet& nodes_, Vec2i coordinates_)
{
    for (auto node : nodes_) {
        if (node->coordinates == coordinates_) {
            return node;
        }
    }
    return nullptr;
}

/**
 * @brief Libère la mémoire allouée pour les nœuds dans une liste.
 *
 * Cette méthode parcourt une liste de nœuds et libère la mémoire allouée pour chaque nœud.
 * Elle supprime chaque nœud de la liste et libère la mémoire associée à l'aide de l'opérateur delete.
 *
 * @param nodes_ La liste de nœuds dont la mémoire doit être libérée.
 */

void AStar::Generator::releaseNodes(NodeSet& nodes_)
{
    for (auto it = nodes_.begin(); it != nodes_.end();) {
        delete *it;
        it = nodes_.erase(it);
    }
}

/**
 * @brief Détermine si des coordonnées spécifiées représentent une collision.
 *
 * Cette méthode vérifie si les coordonnées spécifiées sont en dehors des limites du monde
 * ou correspondent à une position occupée par un mur. Si c'est le cas, elle retourne true,
 * indiquant une collision. Sinon, elle retourne false.
 *
 * @param coordinates_ Les coordonnées à vérifier.
 * @return true si les coordonnées représentent une collision, sinon false.
 */

bool AStar::Generator::detectCollision(Vec2i coordinates_)
{
    if (coordinates_.x < 0 || coordinates_.x >= worldSize.x ||
        coordinates_.y < 0 || coordinates_.y >= worldSize.y ||
        std::find(walls.begin(), walls.end(), coordinates_) != walls.end()) {
        return true;
    }
    return false;
}


//Un point

AStar::Vec2i AStar::Heuristic::getDelta(Vec2i source_, Vec2i target_)
{
    return{ abs(source_.x - target_.x),  abs(source_.y - target_.y) };
}


AStar::uint AStar::Heuristic::manhattan(Vec2i source_, Vec2i target_)
{
    //auto permet d'affecter automatiquement le type de retour de getDelta a delta
    auto delta = getDelta(source_, target_);
    return static_cast<uint>(10 * (delta.x + delta.y));
}

AStar::uint AStar::Heuristic::euclidean(Vec2i source_, Vec2i target_)
{
    auto delta = getDelta(source_, target_);
    return static_cast<uint>(10 * sqrt(pow(delta.x, 2) + pow(delta.y, 2)));
}

AStar::uint AStar::Heuristic::octagonal(Vec2i source_, Vec2i target_)
{
    auto delta = getDelta(source_, target_);
    return 10 * (delta.x + delta.y) + (-6) * std::min(delta.x, delta.y);
}