# Hunter Assassin
Bienvenue dans le jeu Hunter Assassin !

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


🎮🏹 **Bienvenue dans le monde de Hunter Assassin !** 🏹🎮

            _   _   _   _   _   _   _   _   _   _   _   _   _   _   _  
           / \ / \ / \ / \ / \ / \ / \ / \ / \ / \ / \ / \ / \ / \ / \ / \ 
          ( H | u | n | t | e | r |   | A | s | s | a | s | s | i | n | ! )
           \_/ \_/ \_/ \_/ \_/ \_/ \_/ \_/ \_/ \_/ \_/ \_/ \_/ \_/ \_/ \_/ 

🎯 **Préparez-vous pour l'action et l'aventure !** 🎯


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
            <span style="color: #008000;"><strong>src</strong></span>
            <ul>
                <li>
                    <span style="color: #0000ff;"><strong>core</strong></span>
                    <ul>
                        <li><span style="color: #808080;">_Garde.cpp</span></li>
                        <li><span style="color: #808080;">_Garde.h</span></li>
                        <li><span style="color: #808080;">_Player.cpp</span></li>
                        <li><span style="color: #808080;">_Player.h</span></li>
                        <li><span style="color: #808080;">Arrow.h</span></li>
                        <li><span style="color: #808080;">Character.cpp</span></li>
                        <li><span style="color: #808080;">Character.h</span></li>
                        <li><span style="color: #808080;">config.h</span></li>
                        <li><span style="color: #808080;">Direction.h</span></li>
                        <li><span style="color: #808080;">Game.cpp</span></li>
                        <li><span style="color: #808080;">Game.h</span></li>
                        <li><span style="color: #808080;">point.h</span></li>
                        <li><span style="color: #808080;">Rect.h</span></li>
                    </ul>
                </li>
                <li>
                    <span style="color: #0000ff;"><strong>sdl2</strong></span>
                    <ul>
                        <li><span style="color: #808080;">mainProject.cpp</span></li>
                        <li><span style="color: #808080;">SDLAnimation.cpp</span></li>
                        <li><span style="color: #808080;">SDLAnimation.h</span></li>
                        <li><span style="color: #808080;">SDLGame.cpp</span></li>
                        <li><span style="color: #808080;">SDLGame.h</span></li>
                        <li><span style="color: #808080;">SDLSound.cpp</span></li>
                        <li><span style="color: #808080;">SDLSound.h</span></li>
                        <li><span style="color: #808080;">SDLSprite.cpp</span></li>
                        <li><span style="color: #808080;">SDLSprite.h</span></li>
                    </ul>
                </li>
            </ul>
        </li>
        <li><span style="color: #ff0000;">extern</span></li>
        <li><span style="color: #800000;">CMakeLists.txt</span></li>
        <li><span style="color: #800000;">README.md</span></li>
    </ul>
</div>

## Comment jouer

1. Clonez ce dépôt sur votre machine.
2. Configurez les librairies SDL2 selon votre système d'exploitation en suivant les instructions ci-dessus.
3. Utilisez CMake pour générer les fichiers de construction.
4. Compilez le jeu en exécutant la commande `make`.
5. Lancez le jeu en exécutant l'application générée.

## Crédits

Ce jeu a été développé par <span style="color:red">**BAH Mamadou**</span> et <span style="color:red">**Barry Elhadj Amadou**</span>.

## Avertissement

Ce jeu est destiné à un usage personnel uniquement. Veuillez respecter les droits d'auteur et ne pas redistribuer le jeu sans autorisation.

## Licence

Ce projet est sous licence MIT. Veuillez consulter le fichier [LICENSE](LICENSE) pour plus d'informations.
