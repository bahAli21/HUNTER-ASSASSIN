#include "Unit.h"
//#include "Game.h"

// Définition des constantes de vitesse et de taille pour les instances de la classe Unit
const float Unit::speed = 4.7f; // La vitesse de déplacement de l'unité
const float Unit::size = 4; // La taille de l'unité

// Constructeur de la classe Unit
Unit::Unit(SDL_Renderer* renderer, Vector2D setPos) :
        pos(setPos), posDraw(pos) {
    // Initialisation de la position et de la position de dessin de l'unité

    // Chargement de la texture de l'unité
    texture = TextureLoader::loadTexture(renderer, "player.bmp");
    textureArrow = TextureLoader::loadTexture(renderer, "gold-arrow_1.bmp");
}

// Fonction de mise à jour de l'unité
void Unit::update(float dT, Level& level, std::vector<Unit>& listUnits, Character &character) {
    int animation_speed = SDL_GetTicks() / 170;
    int idx = animation_speed % 7;//for walking frame
    int idxAtt= animation_speed % 13; //for animation frame
    int idxDead = animation_speed % 5;

    // Calcul de la distance à la cible depuis la position actuelle de l'unité
    Vector2D targetPos(character.targetPos->x, character.targetPos->y);
    Vector2D destCh(character.dest->x, character.dest->y);
    distanceToTarget = (level.getTargetPos() - pos).magnitude(); //Un type vecteur est retourner par la difference , magnitude() pour l'heristic

    // Calcul de la distance à déplacer pendant cette frame
    //En physique d = v * t haha
    distanceMove = speed * dT;
    if (distanceMove > distanceToTarget) {
        //Yes destination atteinte
        distanceMove = distanceToTarget;
        character.canShootNow = true;
    }else
        character.canShootNow = false;
    // Calcul de la direction de déplacement combinant la direction du champ de flux et de la séparation normale
    Vector2D directionNormalFlowField(level.getFlowNormal((int)pos.x, (int)pos.y)); //Recupere la direction de la tuile
    Vector2D directionNormalSeparation(computeNormalSeparation(listUnits));
    Vector2D directionNormalCombined = directionNormalFlowField + directionNormalSeparation * 5.0f;
    directionNormalCombined.normalize();
    Vector2D posAdd = directionNormalCombined * distanceMove;

    // Vérification des collisions avec les autres unités
    bool moveOk = true;
    for (int i = 0; i < listUnits.size() && moveOk; i++) {
        auto& unitSelected = listUnits[i];
        if (&unitSelected != this && unitSelected.checkOverlap(pos, size)) {
            // Vérification de la direction du mouvement par rapport à l'autre unité
            Vector2D directionToOther = (unitSelected.pos - pos);
            if (directionToOther.magnitude() > 0.01f) {
                Vector2D normalToOther(directionToOther.normalize());
                float angleBtw = abs(normalToOther.angleBetween(directionNormalCombined));
                if (angleBtw < 3.14159265359f / 4.0f)
                    moveOk = false;
            }
        }
    }

    // Mise à jour de la position si aucun obstacle rencontré
    if (moveOk) {
        const float spacing = 0.35f; // Marge de sécurité pour éviter les collisions avec les murs
        int x = (int)(pos.x + posAdd.x + copysign(spacing, posAdd.x)); // Ajustement de la coordonnée x avec la marge de sécurité
        int y = (int)(pos.y + posAdd.y + copysign(spacing, posAdd.y)); // Ajustement de la coordonnée y avec la marge de sécurité

        if (posAdd.x != 0.0f && !level.isTileWall(x, (int)pos.y)) {
            // Vérification de collision sur l'axe x
            pos.x += posAdd.x;
            character.dest->x += 1 * (int)copysign(1, posAdd.x); // Déplace le joueur vers la gauche ou la droite selon la direction de la cible
            int vitesse = 1 * (int)copysign(1, posAdd.x);
            if (vitesse < 0) {
                character.direction = EAST;

                // Si la vitesse est négative, l'unité se déplace vers la gauche
                character.WalkingAnimation(character.player_left_clips, vitesse, idx, WEST); // Utilise l'animation pour le mouvement vers la gauche

            } else {
                character.direction = WEST;
                // Si la vitesse est positive, l'unité se déplace vers la droite
                character.WalkingAnimation(character.player_right_clips, vitesse, idx, EAST); // Utilise l'animation pour le mouvement vers la droite
            }
        }

        if (posAdd.y != 0.0f && !level.isTileWall((int)pos.x, y)) {
            // Vérification de collision sur l'axe y
            pos.y += posAdd.y;
            character.dest->y += 1 * (int)copysign(1, posAdd.y); // Déplace le joueur vers le haut ou le bas selon la direction de la cible
            int vitesse = 1 * (int)copysign(1, posAdd.y);
            if (vitesse < 0) {
                character.direction = NORTH;
                // Si la vitesse est négative, l'unité se déplace vers le haut
                character.WalkingAnimation(character.player_up_clips, vitesse, idx, NORTH); // Utilise l'animation pour le mouvement vers le haut
            } else {
                character.direction = SOUTH;
                // Si la vitesse est positive, l'unité se déplace vers le bas
                character.WalkingAnimation(character.player_down_clips, vitesse, idx, SOUTH); // Utilise l'animation pour le mouvement vers le bas
            }
        }
    }


    //character.updateArrowPos();
    // Calcul de la position de dessin en fonction de la position actuelle
    const float fKeep = 0.93f;
    posDraw = posDraw * fKeep + pos * (1.0f - fKeep);

}



// Fonction de dessin de l'unité
void Unit::draw(SDL_Renderer* renderer, int tileSize, Character character) {
    if (renderer != nullptr) {
        // Dessin de l'unité à sa position de dessin
        SDL_Rect rect = {
                (int)((posDraw.x - size / 2) * tileSize),
                (int)((posDraw.y - size / 2) * tileSize),
                (int)(size * tileSize),
                (int)(size * tileSize) };

        //Angle -90 (up) 0 ou 360 (right) 180(left) et 90(down)
        for (auto arrow: character.listArrow){
            SDL_Rect tmp = {arrow.arrowPos.x,
                            arrow.arrowPos.y,
                            50,
                            50};

            SDL_RenderCopyEx(renderer,
                             textureArrow,
                             nullptr,
                             &tmp,
                             arrow.angleRotate,
                             nullptr,
                             SDL_FLIP_NONE);

        }

        SDL_RenderCopy(renderer, texture,
                       reinterpret_cast<const SDL_Rect *>(character.source),
                       &rect);
    }
}

// Fonction de vérification de chevauchement avec une autre position et taille
bool Unit::checkOverlap(Vector2D posOther, float sizeOther) {
    return (posOther - pos).magnitude() <= (sizeOther + size) / 2.0f;
}

// Fonction de calcul de la séparation normale par rapport aux autres unités
Vector2D Unit::computeNormalSeparation(std::vector<Unit>& listUnits) {
    Vector2D output;

    //Le rayon comme la taille du sprite
    const float radiusSeparation = size;
    for (auto& unitSelected : listUnits) {
        if (&unitSelected != this) {
            // Vérification de la proximité avec l'autre unité
            Vector2D directionToOther = (unitSelected.pos - pos);
            float distanceToOther = directionToOther.magnitude();
            if (distanceToOther <= radiusSeparation) {
                if (directionToOther.magnitude() > 0.01f) {
                    // Ajout de la direction normale à la sortie
                    Vector2D normalToThis(directionToOther.normalize() * -1.0f);
                    output += normalToThis;
                }
            }
        }
    }
    output.normalize();

    return output;
}
