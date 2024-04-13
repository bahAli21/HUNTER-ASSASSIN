# Hunter Assassin

## Description

Hunter Assassin est un jeu d'action et de stratégie dans lequel le joueur incarne un chasseur cherchant à éliminer des gardes sans se faire repérer. Le jeu se déroule dans un environnement 2D avec des graphismes minimalistes et une mécanique de jeu captivante.

## Documentation

La documentation complète du jeu est disponible dans le fichier `index.html` situé dans le dossier `doc/html`.

## Installation

Avant de commencer, assurez-vous d'avoir les éléments suivants installés sur votre système :

- [SDL2](https://www.libsdl.org/)
- [SDL2_image](https://www.libsdl.org/projects/SDL_image/)
- [SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/)
- [SDL2_mixer](https://www.libsdl.org/projects/SDL_mixer/)

### Configuration

#### Windows

Pour les utilisateurs de Windows, suivez ces étapes :

1. Téléchargez et installez les librairies SDL2, SDL2_image, SDL2_ttf et SDL2_mixer depuis les liens fournis ci-dessus.
2. Ouvrez le fichier CMakeLists.txt et modifiez les chemins de destination dans la clause `if(WIN32)` en fonction de l'emplacement où vous avez installé les librairies SDL2.

### Structure des Fichiers

Le projet est organisé comme suit :

.
├── src
│   ├── core
│   │   ├── _Garde.cpp
│   │   ├── _Garde.h
│   │   ├── _Player.cpp
│   │   ├── _Player.h
│   │   ├── Arrow.h
│   │   ├── Character.cpp
│   │   ├── Character.h
│   │   ├── config.h
│   │   ├── Direction.h
│   │   ├── Game.cpp
│   │   ├── Game.h
│   │   ├── point.h
│   │   └── Rect.h
│   └── sdl2
│       ├── mainProject.cpp
│       ├── SDLAnimation.cpp
│       ├── SDLAnimation.h
│       ├── SDLGame.cpp
│       ├── SDLGame.h
│       ├── SDLSound.cpp
│       ├── SDLSound.h
│       ├── SDLSprite.cpp
│       └── SDLSprite.h
├── extern
├── CMakeLists.txt
└── README.md

## Comment jouer

1. Clonez ce dépôt sur votre machine.
2. Configurez les librairies SDL2 selon votre système d'exploitation en suivant les instructions ci-dessus.
3. Utilisez CMake pour générer les fichiers de construction.
4. Compilez le jeu en exécutant la commande `make`.
5. Lancez le jeu en exécutant l'application générée.

## Crédits

Ce jeu a été développé par #BAH Mamadou et #Barry Elhadj Amadou.

## Avertissement

Ce jeu est destiné à un usage personnel uniquement. Veuillez respecter les droits d'auteur et ne pas redistribuer le jeu sans autorisation.

## Licence

Ce projet est sous licence MIT. Veuillez consulter le fichier [LICENSE](LICENSE) pour plus d'informations.
