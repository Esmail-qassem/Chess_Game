cmake_minimum_required(VERSION 3.15)
project(ChessGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tell CMake where to find the SFML package config files
set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/External/lib/cmake/SFML")

# Use static SFML libraries — avoids DLL/runtime version mismatches
set(SFML_STATIC_LIBRARIES TRUE)

# Find SFML 3 — Graphics module (automatically pulls in Window and System)
find_package(SFML 3 REQUIRED COMPONENTS Graphics)

add_subdirectory(src)
