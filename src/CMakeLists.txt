# Cmake minimum version: 2.8
cmake_minimum_required(VERSION 2.8)

# Set the source files
set(SRCS buttons.c enemystore.c eventhandler.c gameover.c highscores.c howtoplay.c imagescale.c inits.c keyboard.c main.c maingame.c mouse.c options.c pause.c physcol.c progressbar.c render.c sprites.c)

# Set the include directories
set(INCLUDES ${CMAKE_SOURCE_DIR}/include ${CHIPMUNK_INCLUDE_DIR} ${ALLEGRO_INCLUDE_DIRS} ${ALLEGRO_INCLUDE_DIRS} ${PHYSFS_DIR})

# Set the libraries needed by this project
set(LIBS ${ALLEGRO_LIBRARIES} liballegro_main.so liballegro_font.so liballegro_image.so liballegro_physfs.so liballegro_primitives.so liballegro_ttf.so liballegro_dialog.so ${CHIPMUNK_LIBRARY} ${PHYSFS_LIBRARY})

# Add the sources, include dirs and libs
add_executable(speedrun ${SRCS})
include_directories(${INCLUDES})
target_link_libraries(speedrun ${LIBS})
