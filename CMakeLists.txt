# Minimum cmake version: 2.8
cmake_minimum_required(VERSION 2.8)

# Project name
project(speedrun)

# Enable debug builds by default
if(CMAKE_BUILD_TYPE STREQUAL "")
	set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules/")
set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install/")

# Default Flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c99 -dM")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -std=c99 -dM")
# If static linking is specified then link staticly with libstdc++
if(SPACECHESS_STATIC_LINK)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -static")
endif(SPACECHESS_STATIC_LINK)


# Debug Flags
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g -pg")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -g -pg")

# Release Flags, no console on windows
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} -O2")
if(WIN32)
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -mwindows")
	set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -mwindows")
endif(WIN32)

# RelWithDebInfo
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELEASE} -g")
set(CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_RELEASE} -g")

# MinSizeRel, no console on windows
set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS} -Os")
set(CMAKE_C_FLAGS_MINSIZEREL "${CMAKE_C_FLAGS} -Os")
if(WIN32)
	set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} -mwindows")
	set(CMAKE_C_FLAGS_MINSIZEREL "${CMAKE_C_FLAGS_MINSIZEREL} -mwindows")
endif(WIN32)

# Requires Allegro, chipmunk and PHYSFS
find_package(Allegro REQUIRED)
find_package(Chipmunk REQUIRED)
find_package(PhysFS REQUIRED)

# Source files in here
add_subdirectory(src)

#install
install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/src/speedrun DESTINATION ./)
install(DIRECTORY resources/buttons/ DESTINATION buttons/)
install(DIRECTORY resources/images/ DESTINATION images/)
install(DIRECTORY resources/fonts/ DESTINATION fonts/)
