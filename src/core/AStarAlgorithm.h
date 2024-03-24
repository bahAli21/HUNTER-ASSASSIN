#ifndef __ASTAR_HPP__
#define __ASTAR_HPP__

#include <vector>
#include <functional> //Pour la fonction heuristique
//#include <set>

namespace AStar
{
    /**
     * @brief Structure représentant des coordonnées 2D entières.
     */
    struct Vec2i
    {
        int x, y;

        /**
         * @brief Surcharge de l'opérateur == pour comparer deux objets Vec2i.
         */
        bool operator == (const Vec2i& coordinates_);

        /**
         * @brief Surcharge de l'opérateur + pour ajouter deux objets Vec2i.
         */
        friend Vec2i operator + (const AStar::Vec2i& optLeft_, const AStar::Vec2i& optRight_) {
            return{ optLeft_.x + optRight_.x, optLeft_.y + optRight_.y };
        }
    };

    /**
 * @brief Alias pour le type unsigned int.
 *
 * Ceci est utilisé pour raccourcir l'écriture de `unsigned int` à `uint`.
 */
    using uint = unsigned int;

/**
 * @brief Alias pour une fonction heuristique dans l'algorithme A*.
 *
 * Une fonction heuristique prend deux paramètres Vec2i (coordonnées source et cible)
 * et retourne un uint représentant l'estimation du coût pour atteindre la cible
 * depuis la source.
 */
    using HeuristicFunction = std::function<uint(Vec2i, Vec2i)>;

/**
 * @brief Alias pour une liste de coordonnées 2D.
 *
 * Ceci est utilisé pour raccourcir l'écriture de `std::vector<Vec2i>` à `CoordinateList`.
 */
    using CoordinateList = std::vector<Vec2i>;


    /**
     * @brief Structure représentant un noeud dans l'algorithme A*.
     */
    /**
  * @brief Structure représentant un noeud dans l'algorithme A*.
  */
    struct Node
    {
        uint G; /**< Coût de déplacement depuis le nœud de départ jusqu'à ce nœud. */
        uint H; /**< Valeur heuristique estimée du coût restant pour atteindre le nœud cible depuis ce nœud. */
        Vec2i coordinates; /**< Coordonnées du nœud dans l'espace. */
        Node *parent; /**< Pointeur vers le nœud parent dans le chemin trouvé. */

        /**
         * @brief Constructeur de Node.
         * @param coord_ Les coordonnées du nœud.
         * @param parent_ Le nœud parent (optionnel, par défaut nullptr).
         */
        Node(Vec2i coord_, Node *parent_ = nullptr);

        /**
         * @brief Calcule le score du nœud (F = G + H).
         * @return Le score du nœud.
         */
        uint getScore(); //F = G+H
    };

    /**
 * @brief Alias pour un ensemble de pointeurs de nœuds.
 *
 * NodeSet est utilisé pour représenter un ensemble de nœuds dans l'algorithme A*,
 * où chaque élément est un pointeur vers un objet Node.
 */
    using NodeSet = std::vector<Node*>;


    class Generator
    {
    public:
        /**
         * @brief Constructeur par défaut de la classe Generator.
         */
        Generator();

        /**
         * @brief Définit la taille du monde dans lequel la recherche de chemin est effectuée.
         * @param worldSize_ Les dimensions du monde.
         */
        void setWorldSize(Vec2i worldSize_);

        /**
         * @brief Active ou désactive le mouvement diagonal.
         * @param enable_ True pour autoriser le mouvement diagonal, false sinon.
         */
        void setDiagonalMovement(bool enable_);

        /**
         * @brief Définit la fonction heuristique utilisée pour estimer le coût restant jusqu'à la destination.
         * @param heuristic_ La fonction heuristique à utiliser.
         */
        void setHeuristic(HeuristicFunction heuristic_);

        /**
         * @brief Trouve le chemin entre deux points dans le monde.
         * @param source_ Les coordonnées du point de départ.
         * @param target_ Les coordonnées du point d'arrivée.
         * @return La liste des coordonnées constituant le chemin trouvé.
         */
        CoordinateList findPath(Vec2i source_, Vec2i target_);

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
        void addCollision(Vec2i topLeft, int width = 0, int height = 0);


        /**
         * @brief Supprime une collision de la liste des obstacles dans le monde.
         * @param coordinates_ Les coordonnées de la collision à supprimer.
         */
        void removeCollision(Vec2i coordinates_);

        /**
         * @brief Efface toutes les collisions de la liste des obstacles dans le monde.
         */
        void clearCollisions();

    private:
        /**
         * @brief Fonction interne pour détecter une collision à des coordonnées spécifiques.
         * @param coordinates_ Les coordonnées à vérifier.
         * @return True s'il y a une collision à ces coordonnées, false sinon.
         */
        bool detectCollision(Vec2i coordinates_);

        /**
         * @brief Recherche un nœud dans une liste de nœuds en fonction de ses coordonnées.
         * @param nodes_ La liste de nœuds à rechercher.
         * @param coordinates_ Les coordonnées du nœud à rechercher.
         * @return Le nœud trouvé ou nullptr s'il n'est pas trouvé.
         */
        Node* findNodeOnList(NodeSet& nodes_, Vec2i coordinates_);

        /**
         * @brief Libère la mémoire allouée pour une liste de nœuds.
         * @param nodes_ La liste de nœuds à libérer.
         */
        void releaseNodes(NodeSet& nodes_);

        HeuristicFunction heuristic; /**< La fonction heuristique utilisée par l'algorithme A*. */
        CoordinateList direction, walls; /**< Les directions possibles et les murs dans le monde. */
        Vec2i worldSize; /**< Les dimensions du monde. */
        uint directions; /**< Le nombre de directions possibles. */
    };


    class Heuristic
    {
        static Vec2i getDelta(Vec2i source_, Vec2i target_);

    public:
        /**
         * @brief Calcule la distance de Manhattan entre deux points.
         * @param source_ Les coordonnées du point source.
         * @param target_ Les coordonnées du point cible.
         * @return La distance de Manhattan entre les deux points.
         */
        static uint manhattan(Vec2i source_, Vec2i target_);

        /**
         * @brief Calcule la distance euclidienne entre deux points.
         * @param source_ Les coordonnées du point source.
         * @param target_ Les coordonnées du point cible.
         * @return La distance euclidienne entre les deux points.
         */
        static uint euclidean(Vec2i source_, Vec2i target_);

        /**
         * @brief Calcule la distance octogonale entre deux points.
         * @param source_ Les coordonnées du point source.
         * @param target_ Les coordonnées du point cible.
         * @return La distance octogonale entre les deux points.
         */
        static uint octagonal(Vec2i source_, Vec2i target_);
    };
}

#endif // __ASTAR_HPP__
