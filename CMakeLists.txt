cmake_minimum_required(VERSION 3.15)
project(ChessGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tell CMake where to find Qt
set(CMAKE_PREFIX_PATH "D:/Qt/6.11.0/msvc2022_64")

# Qt requires these to handle .moc files and resources automatically
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Find Qt6 — Widgets module (includes everything we need for drawing)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_subdirectory(src)
