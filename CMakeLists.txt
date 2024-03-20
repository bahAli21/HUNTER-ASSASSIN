cmake_minimum_required(VERSION 3.26)
project(HunterAssassin)

set(CMAKE_CXX_STANDARD 23)

set(NOYAUTEST_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(HunterAssassin_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

#Les dossiers de base noyau, ihm et txt
set(SRC_CORE_DIR ./src/core)
set(SRC_SDL2_DIR ./src/sdl2)
set(SRC_TXT_DIR ./src/txt)

# Les fichiers sources
set(SRC_CORE ${SRC_CORE_DIR}/Game.cpp ${SRC_CORE_DIR}/Garde.cpp ${SRC_CORE_DIR}/IA.cpp ${SRC_CORE_DIR}/Player.cpp)
set(HEADER_CORE ${SRC_CORE_DIR}/Game.h ${SRC_CORE_DIR}/Garde.h ${SRC_CORE_DIR}/IA.h ${SRC_CORE_DIR}/Player.h ${SRC_CORE_DIR}/point.h ${SRC_CORE_DIR}/Rect.h ${SRC_CORE_DIR}/config.h)
set(SRC_SDL2 ${SRC_SDL2_DIR}/mainProject.cpp ${SRC_SDL2_DIR}/SDLGame.cpp ${SRC_SDL2_DIR}/SDLGame.h ${SRC_SDL2_DIR}/SDLSprite.h ${SRC_SDL2_DIR}/SDLSprite.cpp )
set(SRC_TXT ${SRC_TXT_DIR}/main_txt.cpp ${SRC_TXT_DIR}/gameTxt.cpp ${SRC_TXT_DIR}/winTxt.h ${SRC_TXT_DIR}/winTxt.cpp ${SRC_TXT_DIR}/gameTxt.h)
set(SRC_ANIMATION ${PROJECT_SOURCE_DIR}/src/mainAnimation.cpp ${PROJECT_SOURCE_DIR}/map/map.cpp ${PROJECT_SOURCE_DIR}/map/map.h)

# Les libs (SDL2)
if (WIN32)
    # lib SDL2
    set(SDL2_DIR ${PROJECT_SOURCE_DIR}/extern/SDL2_mingw-cb20/SDL2-2.0.12/x86_64-w64-mingw32)
    set(SDL2_INCLUDE_DIR ${SDL2_DIR}/include/SDL2)
    set(SDL2_LIBRARY ${SDL2_DIR}/lib)

    # lib SDL2 image
    set(SDL2_IMAGE_DIR ${PROJECT_SOURCE_DIR}/extern/SDL2_mingw-cb20/SDL2_image-2.0.5/x86_64-w64-mingw32)
    set(SDL2_IMAGE_INCLUDE_DIR ${SDL2_IMAGE_DIR}/include/SDL2)
    set(SDL2_IMAGE_LIBRARY ${SDL2_IMAGE_DIR}/lib)

    # lib SDL2 ttf
    set(SDL2_TTF_DIR ${PROJECT_SOURCE_DIR}/extern/SDL2_mingw-cb20/SDL2_ttf-2.0.15/x86_64-w64-mingw32)
    set(SDL2_TTF_INCLUDE_DIR ${SDL2_TTF_DIR}/include/SDL2)
    set(SDL2_TTF_LIBRARY ${SDL2_TTF_DIR}/lib)

    # lib SDL2 mixer
    set(SDL2_MIXER_DIR ${PROJECT_SOURCE_DIR}/extern/SDL2_mingw-cb20/SDL2_mixer-2.0.4/x86_64-w64-mingw32)
    set(SDL2_MIXER_INCLUDE_DIR ${SDL2_MIXER_DIR}/include/SDL2)
    set(SDL2_MIXER_LIBRARY ${SDL2_MIXER_DIR}/lib)
endif (WIN32)

#Mes executables
add_executable(HunterAssassin ${SRC_CORE} ${HEADER_CORE} ${SRC_SDL2})
add_executable(JeuTxt ${SRC_CORE} ${HEADER_CORE} ${SRC_TXT})
add_executable(Animation ${SRC_ANIMATION})

set_target_properties(HunterAssassin PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${HunterAssassin_OUTPUT_PATH}
)

set_target_properties(Animation PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${HunterAssassin_OUTPUT_PATH}
)

set_target_properties(JeuTxt PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${HunterAssassin_OUTPUT_PATH}
)

# Options de compilation CXX
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -ggdb")

# Include compilation
target_include_directories(Animation PUBLIC ${SRC_CORE_DIR} ${SRC_SDL2_DIR} ${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR} ${SDL2_MIXER_INCLUDE_DIR})
target_include_directories(HunterAssassin PUBLIC ${SRC_CORE_DIR} ${SRC_SDL2_DIR} ${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR} ${SDL2_MIXER_INCLUDE_DIR})
target_include_directories(JeuTxt PUBLIC ${SRC_CORE_DIR} ${SRC_TXT})

# L'édition des liens
target_link_directories(HunterAssassin PUBLIC ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_TTF_LIBRARY} ${SDL2_MIXER_LIBRARY})
# L'édition des liens
target_link_directories(Animation PUBLIC ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_TTF_LIBRARY} ${SDL2_MIXER_LIBRARY})

# Librairies édition des liens
if (WIN32)
    target_link_libraries(HunterAssassin mingw32 SDL2main SDL2 SDL2_image SDL2_ttf SDL2_mixer)
    target_link_libraries(Animation mingw32 SDL2main SDL2 SDL2_image SDL2_ttf SDL2_mixer)
endif (WIN32)

# Copie les dll de SDL si Win32
if (WIN32)
    file(COPY ${SDL2_DIR}/bin/SDL2.dll ${SDL2_IMAGE_DIR}/bin/libjpeg-9.dll ${SDL2_IMAGE_DIR}/bin/libpng16-16.dll ${SDL2_IMAGE_DIR}/bin/libtiff-5.dll ${SDL2_IMAGE_DIR}/bin/libwebp-7.dll ${SDL2_IMAGE_DIR}/bin/SDL2_image.dll ${SDL2_IMAGE_DIR}/bin/zlib1.dll ${SDL2_TTF_DIR}/bin/libfreetype-6.dll ${SDL2_TTF_DIR}/bin/SDL2_ttf.dll ${SDL2_MIXER_DIR}/bin/libFLAC-8.dll ${SDL2_MIXER_DIR}/bin/libmodplug-1.dll ${SDL2_MIXER_DIR}/bin/libmpg123-0.dll ${SDL2_MIXER_DIR}/bin/libogg-0.dll ${SDL2_MIXER_DIR}/bin/libopus-0.dll ${SDL2_MIXER_DIR}/bin/libopusfile-0.dll ${SDL2_MIXER_DIR}/bin/libvorbis-0.dll ${SDL2_MIXER_DIR}/bin/libvorbisfile-3.dll ${SDL2_MIXER_DIR}/bin/SDL2_mixer.dll DESTINATION ${CMAKE_BINARY_DIR})
endif (WIN32)


#target_link_libraries(HunterAssassin ${SDL2_LIBRARY})
#target_link_libraries(Animation ${SDL2_LIBRARY})
