🎮🏹 **Bienvenue dans le monde de Hunter Assassin !** 🏹🎮

            _   _   _   _   _   _   _   _   _   _   _   _   _   _   _  
           / \ / \ / \ / \ / \ / \ / \ / \ / \ / \ / \ / \ / \ / \ / \ / \ 
          ( H | u | n | t | e | r |   | A | s | s | a | s | s | i | n | ! )
           \_/ \_/ \_/ \_/ \_/ \_/ \_/ \_/ \_/ \_/ \_/ \_/ \_/ \_/ \_/ \_/ 

🎯 **Préparez-vous pour l'action et l'aventure !** 🎯
           .--.        .-.
          : (\ ". _..._ .' /) :
           '.    `        `    .'
            /'   _        _   `\
          \/     0}      {0     \/
          /   /                 \   \
          / /   /             \   \ \
          /   /'               `\   \
          /   /                   \   \

         

Veuillez lire les instructions ci-dessous pour commencer à jouer !

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
<div style="font-family: monospace;">
    <ul>
        <li>
            <strong>src</strong>
            <ul>
                <li>
                    <strong>core</strong>
                    <ul>
                        <li><code>_Garde.cpp</code></li>
                        <li><code>_Garde.h</code></li>
                        <li><code>_Player.cpp</code></li>
                        <li><code>_Player.h</code></li>
                        <li><code>Arrow.h</code></li>
                        <li><code>Character.cpp</code></li>
                        <li><code>Character.h</code></li>
                        <li><code>config.h</code></li>
                        <li><code>Direction.h</code></li>
                        <li><code>Game.cpp</code></li>
                        <li><code>Game.h</code></li>
                        <li><code>point.h</code></li>
                        <li><code>Rect.h</code></li>
                    </ul>
                </li>
                <li>
                    <strong>sdl2</strong>
                    <ul>
                        <li><code>mainProject.cpp</code></li>
                        <li><code>SDLAnimation.cpp</code></li>
                        <li><code>SDLAnimation.h</code></li>
                        <li><code>SDLGame.cpp</code></li>
                        <li><code>SDLGame.h</code></li>
                        <li><code>SDLSound.cpp</code></li>
                        <li><code>SDLSound.h</code></li>
                        <li><code>SDLSprite.cpp</code></li>
                        <li><code>SDLSprite.h</code></li>
                    </ul>
                </li>
            </ul>
        </li>
        <li><strong>extern</strong></li>
        <li><strong>CMakeLists.txt</strong></li>
        <li><strong>README.md</strong></li>
    </ul>
</div>


## Comment jouer

1. Clonez ce dépôt sur votre machine.
2. Configurez les librairies SDL2 selon votre système d'exploitation en suivant les instructions ci-dessus.
3. Utilisez CMake pour générer les fichiers de construction.
4. Compilez le jeu en exécutant la commande `make`.
5. Lancez le jeu en exécutant l'application générée.

## Crédits

Ce jeu a été développé par [BAH Mamadou](https://github.com/bahAli21) et [Barry Elhadj Amadou](https://github.com/barryelhadj).


## Avertissement

Ce jeu est destiné à un usage personnel uniquement. Veuillez respecter les droits d'auteur et ne pas redistribuer le jeu sans autorisation.

## Licence

Ce projet est sous licence MIT. Veuillez consulter le fichier [LICENSE](LICENSE) pour plus d'informations.
