cmake_minimum_required(VERSION 3.26)
project(hunterassassin)

set(CMAKE_CXX_STANDARD 23)

set(NOYAUTEST_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(HUNTERASSASSIN_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/build)
set(SDL2_PATH "D:/SDL2-2.30.0/x86_64-w64-mingw32")
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

add_executable(hunterassassin src/sdl2/mainProject.cpp
        src/sdl2/SDLGame.cpp
        #src/sdl2/SDLGame.h
        src/sdl2/SDLSprite.cpp
        #src/sdl2/SDLSprite.h
        src/core/Game.cpp
        #src/core/Game.h
        #src/core/config.h
        src/core/Player.cpp
        #src/core/Player.h
        #src/core/Rect.h
        src/core/IA.cpp
        #src/core/IA.h
        src/core/Map.cpp
        #src/core/Map.h
        src/core/Garde.cpp
        src/sdl2/SDLAnimation.h
        #src/core/Garde.h
        src/sdl2/SDLAnimation.h
        src/sdl2/SDLAnimation.cpp
)

add_executable(Animation src/mainAnimation.cpp
        #map/map.h
        map/map.cpp
        map/color.h

)

add_executable(JeuTxt src/txt/main_txt.cpp
        src/txt/gameTxt.cpp
        src/txt/winTxt.cpp
        #src/txt/gameTxt.h
        src/txt/winTxt.h
        src/core/Game.cpp
        #src/core/Game.h
        #src/core/Player.h
        src/core/Player.cpp
        #src/core/Garde.h
        src/core/Garde.cpp
        src/core/Map.cpp
        #src/core/Map.h
)

set_target_properties(hunterassassin PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${HUNTERASSASSIN_OUTPUT_PATH}
)

set_target_properties(Animation PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${HUNTERASSASSIN_OUTPUT_PATH}
)

set_target_properties(JeuTxt PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${HUNTERASSASSIN_OUTPUT_PATH}
)



target_link_libraries(hunterassassin ${SDL2_LIBRARY})
target_link_libraries(Animation ${SDL2_LIBRARY})
