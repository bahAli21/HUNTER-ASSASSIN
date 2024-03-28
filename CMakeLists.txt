# Définition de la version minimale de CMake requise
cmake_minimum_required(VERSION 3.26)

# Définition du nom du projet
project(HunterAssassin)

# Définition du standard C++ utilisé
set(CMAKE_CXX_STANDARD 23)

# Définition des chemins de sortie pour les exécutables
set(NOYAUTEST_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(HunterAssassin_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(OBJ_DIR ${PROJECT_SOURCE_DIR}/obj)
# Définition des dossiers sources
set(SRC_CORE_DIR ./src/core)
set(SRC_SDL2_DIR ./src/sdl2)
set(SRC_TXT_DIR ./src/txt)
set(SRC_ASTAR_DIR ./src/Part2)

set(SRC_ASTAR ${SRC_ASTAR_DIR}/Game.cpp
        ${SRC_ASTAR_DIR}/Level.cpp
        ${SRC_ASTAR_DIR}/TextureLoader.cpp
        ${SRC_ASTAR_DIR}/Unit.cpp
        ${SRC_ASTAR_DIR}/Vector2D.cpp
        ${SRC_ASTAR_DIR}/main.cpp
        ${SRC_SDL2_DIR}/SDLAnimation.cpp
        ${SRC_SDL2_DIR}/SDLSprite.h
        ${SRC_SDL2_DIR}/SDLSprite.cpp
        ${SRC_CORE_DIR}/Player.cpp
        ${SRC_SDL2_DIR}/SDLSound.cpp
        ${SRC_CORE_DIR}/Game.cpp
        ${SRC_CORE_DIR}/IA.cpp
        ${SRC_CORE_DIR}/Garde.cpp
)

# Définition des fichiers sources pour chaque composant
set(SRC_CORE ${SRC_CORE_DIR}/Game.cpp ${SRC_CORE_DIR}/Garde.cpp ${SRC_CORE_DIR}/IA.cpp
        ${SRC_CORE_DIR}/Player.cpp
        #${SRC_CORE_DIR}/newIA.cpp
        src/sdl2/SDLSound.cpp
)

set(HEADER_CORE ${SRC_CORE_DIR}/Game.h ${SRC_CORE_DIR}/Garde.h
        ${SRC_CORE_DIR}/IA.h ${SRC_CORE_DIR}/Player.h ${SRC_CORE_DIR}/point.h
        ${SRC_CORE_DIR}/Rect.h ${SRC_CORE_DIR}/config.h
        src/core/Direction.h
        src/core/Arrow.h
        src/sdl2/SDLTtf.h
        src/sdl2/SDLTtf.cpp
        src/sdl2/SDLSound.h
)

set(SRC_SDL2 ${SRC_SDL2_DIR}/mainProject.cpp ${SRC_SDL2_DIR}/SDLGame.cpp
        ${SRC_SDL2_DIR}/SDLGame.h ${SRC_SDL2_DIR}/SDLSprite.h ${SRC_SDL2_DIR}/SDLSprite.cpp
        src/sdl2/SDLAnimation.cpp
)

set(SRC_TXT ${SRC_TXT_DIR}/main_txt.cpp ${SRC_TXT_DIR}/gameTxt.cpp
        ${SRC_TXT_DIR}/winTxt.h ${SRC_TXT_DIR}/winTxt.cpp ${SRC_TXT_DIR}/gameTxt.h)

set(SRC_ANIMATION ${PROJECT_SOURCE_DIR}/src/mainAnimation.cpp
        ${PROJECT_SOURCE_DIR}/map/map.cpp ${PROJECT_SOURCE_DIR}/map/map.h
        src/sdl2/SDLTtf.h
        src/sdl2/SDLTtf.cpp
        src/sdl2/SDLSound.h
        src/sdl2/SDLSound.cpp
        src/core/Direction.h
)

# Configuration des librairies SDL2 en fonction du système d'exploitation
if (WIN32)
    set(SDL2_DIR ${PROJECT_SOURCE_DIR}/extern/SDL2_mingw-cb20/SDL2-2.0.12/x86_64-w64-mingw32)
    set(SDL2_INCLUDE_DIR ${SDL2_DIR}/include/SDL2)
    set(SDL2_LIBRARY ${SDL2_DIR}/lib)

    set(SDL2_IMAGE_DIR ${PROJECT_SOURCE_DIR}/extern/SDL2_mingw-cb20/SDL2_image-2.0.5/x86_64-w64-mingw32)
    set(SDL2_IMAGE_INCLUDE_DIR ${SDL2_IMAGE_DIR}/include/SDL2)
    set(SDL2_IMAGE_LIBRARY ${SDL2_IMAGE_DIR}/lib)

    set(SDL2_TTF_DIR ${PROJECT_SOURCE_DIR}/extern/SDL2_mingw-cb20/SDL2_ttf-2.0.15/x86_64-w64-mingw32)
    set(SDL2_TTF_INCLUDE_DIR ${SDL2_TTF_DIR}/include/SDL2)
    set(SDL2_TTF_LIBRARY ${SDL2_TTF_DIR}/lib)

    set(SDL2_MIXER_DIR ${PROJECT_SOURCE_DIR}/extern/SDL2_mingw-cb20/SDL2_mixer-2.0.4/x86_64-w64-mingw32)
    set(SDL2_MIXER_INCLUDE_DIR ${SDL2_MIXER_DIR}/include/SDL2)
    set(SDL2_MIXER_LIBRARY ${SDL2_MIXER_DIR}/lib)
endif (WIN32)

if (UNIX)
    set(SDL2_INCLUDE_DIR /usr/include/SDL2)
    set(SDL2_LIBRARY /usr/lib)

    set(SDL2_IMAGE_INCLUDE_DIR ${SDL2_INCLUDE_DIR})
    set(SDL2_IMAGE_LIBRARY ${SDL2_LIBRARY})

    set(SDL2_TTF_INCLUDE_DIR ${SDL2_INCLUDE_DIR})
    set(SDL2_TTF_LIBRARY ${SDL2_LIBRARY})

    set(SDL2_MIXER_INCLUDE_DIR ${SDL2_INCLUDE_DIR})
    set(SDL2_MIXER_LIBRARY ${SDL2_LIBRARY})
endif (UNIX)

# Définition des exécutables

add_executable(HunterAssassin ${SRC_CORE} ${HEADER_CORE} ${SRC_SDL2})
add_executable(JeuTxt ${SRC_CORE} ${HEADER_CORE} ${SRC_TXT})
add_executable(Animation ${SRC_ANIMATION})
add_executable(ASTAR ${SRC_ASTAR})

# Configuration des propriétés des exécutables
set_target_properties(HunterAssassin PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${HunterAssassin_OUTPUT_PATH})
set_target_properties(Animation PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${HunterAssassin_OUTPUT_PATH})
set_target_properties(JeuTxt PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${HunterAssassin_OUTPUT_PATH})
set_target_properties(ASTAR PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${HunterAssassin_OUTPUT_PATH})

# Configuration de la sortie pour les fichiers objets
set_target_properties(HunterAssassin PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${OBJ_DIR})
set_target_properties(Animation PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${OBJ_DIR})
set_target_properties(JeuTxt PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${OBJ_DIR})

# Options de compilation C++
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -ggdb")

# Inclusion des fichiers de compilation
target_include_directories(Animation PUBLIC ${SRC_CORE_DIR} ${SRC_SDL2_DIR} ${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR} ${SDL2_MIXER_INCLUDE_DIR})
target_include_directories(HunterAssassin PUBLIC ${SRC_CORE_DIR} ${SRC_SDL2_DIR} ${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR} ${SDL2_MIXER_INCLUDE_DIR})
target_include_directories(JeuTxt PUBLIC ${SRC_CORE_DIR} ${SRC_TXT})
target_include_directories(ASTAR PUBLIC ${SRC_CORE_DIR} ${SRC_SDL2_DIR} ${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR} ${SDL2_MIXER_INCLUDE_DIR})

# Liaison des librairies
target_link_directories(HunterAssassin PUBLIC ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_TTF_LIBRARY} ${SDL2_MIXER_LIBRARY})
target_link_directories(Animation PUBLIC ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_TTF_LIBRARY} ${SDL2_MIXER_LIBRARY})
target_link_directories(ASTAR PUBLIC ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_TTF_LIBRARY} ${SDL2_MIXER_LIBRARY})
# Configuration des librairies selon le système d'exploitation
if (WIN32)
    target_link_libraries(HunterAssassin mingw32 SDL2main SDL2 SDL2_image SDL2_ttf SDL2_mixer)
    target_link_libraries(Animation mingw32 SDL2main SDL2 SDL2_image SDL2_ttf SDL2_mixer)
    target_link_libraries(ASTAR mingw32 SDL2main SDL2 SDL2_image SDL2_ttf SDL2_mixer)
endif (WIN32)

if (UNIX)
    target_link_libraries(HunterAssassin SDL2 SDL2_image SDL2_ttf SDL2_mixer GL)
    target_link_libraries(Animation SDL2 SDL2_image SDL2_ttf SDL2_mixer GL)
endif (UNIX)

# Copie des fichiers DLL SDL pour Windows
if (WIN32)
    file(COPY ${SDL2_DIR}/bin/SDL2.dll ${SDL2_IMAGE_DIR}/bin/libjpeg-9.dll ${SDL2_IMAGE_DIR}/bin/libpng16-16.dll ${SDL2_IMAGE_DIR}/bin/libtiff-5.dll ${SDL2_IMAGE_DIR}/bin/libwebp-7.dll ${SDL2_IMAGE_DIR}/bin/SDL2_image.dll ${SDL2_IMAGE_DIR}/bin/zlib1.dll ${SDL2_TTF_DIR}/bin/libfreetype-6.dll ${SDL2_TTF_DIR}/bin/SDL2_ttf.dll ${SDL2_MIXER_DIR}/bin/libFLAC-8.dll ${SDL2_MIXER_DIR}/bin/libmodplug-1.dll ${SDL2_MIXER_DIR}/bin/libmpg123-0.dll ${SDL2_MIXER_DIR}/bin/libogg-0.dll ${SDL2_MIXER_DIR}/bin/libopus-0.dll ${SDL2_MIXER_DIR}/bin/libopusfile-0.dll ${SDL2_MIXER_DIR}/bin/libvorbis-0.dll ${SDL2_MIXER_DIR}/bin/libvorbisfile-3.dll ${SDL2_MIXER_DIR}/bin/SDL2_mixer.dll DESTINATION ${CMAKE_BINARY_DIR})
endif (WIN32)
